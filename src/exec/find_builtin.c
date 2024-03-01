/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 09:32:17 by lgarfi            #+#    #+#             */
/*   Updated: 2024/02/26 12:41:25 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/*
◦ echo with option -n
◦ cd with only a relative or absolute path
◦ pwd with no options
◦ export with no options
◦ unset with no options
◦ env with no options or arguments
◦ exit with no options
*/

int	ft_find_builtin2(char *cmd, char **cmd_tab, char ***env)
{
	int	status;

	status = 0;
	if (ft_strcmp(cmd, "exit") == 0)
	{
		status = ft_exit(cmd_tab);
		return (status);
	}
	else if (ft_strcmp(cmd, "unset") == 0) 
	{
		status = ft_unset(env, cmd_tab); // a modifier pour pouvoir faire plusieurs unset
		return (status);
		}
	else if (ft_strcmp(cmd, "export") == 0)
	{
		status = ft_export(env, cmd_tab, 0); // pareil
		return (status);
	}
	else if (ft_strcmp(cmd, "env") == 0)
	{
		status = ft_env(*env);
		return (status);
	}
	return (-1);
}

int	ft_find_builtin(char *cmd, char **cmd_tab, char ***env)
{
	int	status;

	status = 0;
	if (ft_strcmp(cmd, "cd") == 0)
	{
		status = ft_cd(cmd_tab, env);
		return (status);
	}
	else if (ft_strcmp(cmd, "echo") == 0)
	{
		status = ft_echo(cmd_tab);
		return (status);
	}
	else if (ft_strcmp(cmd, "pwd") == 0)
	{
		status = ft_pwd(cmd_tab);
		return (status);
	}
	else
		status = ft_find_builtin2(cmd, cmd_tab, env);
	return (status);
}

int	ft_is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0) 
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (1);
	return (0);
}
