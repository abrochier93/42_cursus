/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrochie <abrochie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 19:55:17 by abrochie          #+#    #+#             */
/*   Updated: 2023/07/03 19:55:18 by abrochie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	print_perror_msg(char *path)
{
	char	*error_msg;	

	error_msg = ft_strjoin("miishell: cd: ", path);
	perror(error_msg);
	free(error_msg);
	return (EXIT_FAILURE);
}

static void	update_pwd(t_mini *data)
{
	char	cwd[PATH_MAX];
	char	*updated_var;

	getcwd(cwd, PATH_MAX);
	updated_var = ft_strjoin("PWD=", cwd);
	save_user_vars(updated_var, &data->envp_lst, true);
	free(updated_var);
}

static void	update_oldpwd(char *temp, t_mini *data)
{
	char	*oldpwd;

	oldpwd = ft_strjoin("OLDPWD=", temp);
	save_user_vars(oldpwd, &data->envp_lst, true);
	free(oldpwd);
}

static int	cd_oldpwd(char *temp, t_mini *data)
{
	char	*oldpwd;

	oldpwd = get_fromvlst("OLDPWD", &data->envp_lst);
	if (!oldpwd)
	{
		ft_putendl_fd(OLDPWD_NOT_SET, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (chdir(oldpwd) == SUCCESS)
	{
		ft_putendl_fd(oldpwd, STDOUT_FILENO);
		update_oldpwd(&temp[0], data);
		update_pwd(data);
		return (EXIT_SUCCESS);
	}
	return (print_perror_msg(oldpwd));
}

int	cmd_cd(char *path, t_mini *data)
{
	char	temp[PATH_MAX];

	getcwd(temp, PATH_MAX);
	if (path == NULL || streq(path, "~"))
	{
		update_oldpwd(&temp[0], data);
		chdir(getenv("HOME"));
		update_pwd(data);
		return (EXIT_SUCCESS);
	}
	if (streq(path, "-"))
		return (cd_oldpwd(&temp[0], data));
	if (chdir(path) == SUCCESS)
	{
		update_oldpwd(&temp[0], data);
		update_pwd(data);
		return (EXIT_SUCCESS);
	}
	return (print_perror_msg(path));
}
