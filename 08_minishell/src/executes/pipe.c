/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrochie <abrochie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 19:56:09 by abrochie          #+#    #+#             */
/*   Updated: 2023/07/03 19:56:10 by abrochie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern long long	g_exit_status;

static void	left_side(t_statement *nd, t_mini *data, int pdes[2])
{
	close(STDOUT_FILENO);
	dup(pdes[1]);
	close(pdes[0]);
	close(pdes[1]);
	exec_cmd(nd, data);
}

static void	right_side(t_statement *nd, t_mini *data, int pdes[2])
{
	close(STDIN_FILENO);
	dup(pdes[0]);
	close(pdes[0]);
	close(pdes[1]);
	exec_cmd(nd, data);
}

void	exec_pipe(t_statement *node, t_mini *data)
{
	pid_t	child_pid;
	int		pipedes[2];
	int		temp_status;

	node->operator = NONE;
	if (pipe(pipedes) == -1)
		error(data, PIPE_ERR, EXIT_FAILURE);
	child_pid = fork();
	if (child_pid == -1)
		error(data, FORK_ERR, EXIT_FAILURE);
	if (child_pid == 0)
		left_side(node, data, pipedes);
	right_side(node->next, data, pipedes);
	close(pipedes[0]);
	close(pipedes[1]);
	waitpid(child_pid, &temp_status, 0);
	g_exit_status = temp_status >> 8;
}

/* 127, i.e command not found, comes from waitpid as 32512. 32512 >> 8 = 127 */