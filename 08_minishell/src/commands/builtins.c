/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrochie <abrochie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 19:55:55 by abrochie          #+#    #+#             */
/*   Updated: 2023/07/03 19:55:56 by abrochie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern long long	g_exit_status;

bool	is_valid_id(char *str)
{
	size_t	i;

	i = 0;
	if (streq(str, "="))
		return (false);
	while (str[i] && str[i] != '=')
	{
		if (ft_isdigit(str[i]) || str[i] == '!' || str[i] == '@'
			|| str[i] == '{' || str[i] == '}' || str[i] == '-')
			return (false);
		i += 1;
	}
	return (true);
}

static int	call_cmd_unset(t_statement *s, t_mini *data)
{
	if (s->argc == 1)
		return (EXIT_SUCCESS);
	return (cmd_unset(s, &data->envp_lst));
}

static int	call_cmd_cd(t_statement *s, t_mini *data)
{
	if (s->argc > 2)
		return (cd_too_many_args());
	else
		return (cmd_cd(s->argv[1], data));
}

static int	call_cmd_echo(t_statement *s)
{
	t_statement	*temp;
	bool		has_n;

	temp = s;
	has_n = false;
	if (s->argc >= 2)
		has_n = streq(s->argv[1], "-n");
	cmd_echo(temp, has_n);
	temp = temp->next;
	while (temp != NULL && temp->argc > 2)
	{
		cmd_echo(temp, false);
		if (temp->operator == PIPE)
			break ;
		temp = temp->next;
	}
	if (!has_n)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

bool	builtin(t_statement *s, t_mini *data)
{
	if (streq(s->argv[0], "env") && 
		get_fromvlst("PATH", &data->envp_lst) != NULL)
		g_exit_status = cmd_env(data);
	else if (streq(s->argv[0], "cd") && 
		get_fromvlst("PATH", &data->envp_lst) != NULL)
		g_exit_status = call_cmd_cd(s, data);
	else if (streq(s->argv[0], "exit"))
		cmd_exit(s, data);
	else if (streq(s->argv[0], "unset") || streq(s->argv[0], "unsetenv"))
		g_exit_status = call_cmd_unset(s, data);
	else if (streq(s->argv[0], "export") || streq(s->argv[0], "setenv"))
		g_exit_status = cmd_export(s, data);
	else if (ft_strchr(s->argv[0], '=') && is_valid_id(s->argv[0]))
		g_exit_status = save_user_vars(s->argv[0],
				&data->envp_lst, false);
	else if (streq(s->argv[0], "echo"))
		g_exit_status = call_cmd_echo(s);
	else if (streq(s->argv[0], "pwd"))
		g_exit_status = cmd_pwd();
	else
		return (false);
	return (true);
}
