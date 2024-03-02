/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 21:20:57 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/01 21:22:39 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_change_owd_old_pwd2(char ***env, char *current_path, int check)
{
	char	*exp_n_old_pwd;
	char	*exp_val_old_pwd;
	char	*exp_str_old_pwd;

	exp_n_old_pwd = NULL;
	exp_val_old_pwd = NULL;
	exp_str_old_pwd = NULL;
	if (is_export_name_in_env(*env, "OLDPWD") != 1 \
		|| is_export_name_in_env(*env, "OLDPWD"))
	{
		exp_n_old_pwd = ft_str_dup_env("OLDPWD=", exp_n_old_pwd);
		exp_val_old_pwd = ft_str_dup_env(current_path, exp_val_old_pwd);
		exp_str_old_pwd = ft_strjoin_equal_val(exp_n_old_pwd, exp_val_old_pwd);
		if (check == 1)
			ft_export2(env, exp_str_old_pwd);
		free(exp_str_old_pwd);
	}
}

void	ft_change_pwd_old_pwd(char *current_path, char *new_path, char ***env)
{
	char	*exp_n_new;
	char	*exp_val_new;
	char	*exp_str_new;
	int		check;

	check = 0;
	exp_n_new = NULL;
	exp_val_new = NULL;
	exp_str_new = NULL;
	if (is_export_name_in_env(*env, "PWD") != -1)
	{
		exp_n_new = ft_str_dup_env("PWD=", exp_n_new);
		exp_val_new = ft_str_dup_env(new_path, exp_val_new);
		exp_str_new = ft_strjoin_equal_val(exp_n_new, exp_val_new);
		ft_export2(env, exp_str_new);
		free(exp_str_new);
		check = 1;
	}
	ft_change_owd_old_pwd2(env, current_path, check);
	return ;
}

int	is_export_name_in_env(char **env, char *str)
{
	int		i;
	char	*export_name;

	i = 0;
	while (env[i])
	{
		export_name = ft_find_export_name(env[i]);
		if (ft_strcmp(export_name, str) == 0)
		{
			free(export_name);
			return (i);
		}
		free(export_name);
		i++;
	}
	return (-1);
}

int	ft_cdpath(char **pathtab)
{
	char	**cdpath;
	char	*str_cdpath;
	int		i;

	cdpath = ft_split(getenv("cdpath"), ':');
	i = -1;
	while (cdpath[++i])
	{
		str_cdpath = ft_strjoin_path_without_free(cdpath[i], pathtab[1]);
		if (chdir(str_cdpath) == 0)
		{
			printf("%s\n", str_cdpath);
			free(str_cdpath);
			free_tab_tab(cdpath);
			return (0);
		}
		free(str_cdpath);
	}
	free_tab_tab(cdpath);
	return (-1);
}

int	ft_msg_err_chdir(char *str)
{
	char	*first_part;
	char	*second_part;
	char	*err_msg;

	first_part = ft_strjoin_wihtout_free("bash: cd: ", str);
	if (!first_part)
		return (ERROR_MALLOC);
	second_part = ft_strjoin_wihtout_free(": No such", " file or directory\n");
	if (!first_part)
		return (ERROR_MALLOC);
	err_msg = ft_strjoin_wihtout_free(first_part, second_part);
	if (!first_part)
		return (ERROR_MALLOC);
	ft_putstr_fd(err_msg, 2);
	free(first_part);
	free(second_part);
	free(err_msg);
	return (0);
}
