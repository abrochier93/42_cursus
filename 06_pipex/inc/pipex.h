/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrochie <abrochie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 07:49:45 by abrochie          #+#    #+#             */
/*   Updated: 2023/04/24 18:00:01 by abrochie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <errno.h>
# include <string.h>

# define PATH 5
# define START 6

typedef struct s_cmd
{
	char	*cmd;
	char	**path;
	char	*args[100];
	int		f;
}	t_cmd;

void	pipex(int f1, int f2, char **ag, char **ep);
void	exec_cmd(t_cmd *cmd1, t_cmd *cmd2, char **envp);
void	error_msg(char *c);
int		check_cmd(t_cmd *c);
int		check_empty(char *s);

/*
* STRING UTILS
*/

char	**ft_splitpath(char *s, char c);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strdup(const char *src);
int		ft_putstr(char *s, char *t);
char	**get_path(char **ep);
void	error_msg_path(void);

/*
* FREE
*/

int		free_arr(char **path);
void	free_struct(t_cmd *c);
#endif