/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 09:32:17 by lgarfi            #+#    #+#             */
/*   Updated: 2024/01/30 14:21:59 by lgarfi           ###   ########.fr       */
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

int	ft_find_builtin2(char *cmd, char **cmd_tab, char **env)
{
	if (ft_strcmp(cmd, "exit") == 0)
	{
		ft_exit(cmd_tab);
		return (1);
	}
	else if (ft_strcmp(cmd, "unset") == 0) 
	{
		ft_unset(env,cmd_tab[1]); // a modifier pour pouvoir faire plusieurs unset
		return (1);
	}
	else if (ft_strcmp(cmd, "export") == 0)
	{
		ft_export(env, cmd_tab[1]); // pareil
		return (1);
	}
	else if (ft_strcmp(cmd, "env") == 0)
	{
		ft_env(env);
		return (1);
	}
	return (0);
}

int	ft_find_builtin(char *cmd, char **cmd_tab, char **env)
{
	if (ft_strcmp(cmd, "cd") == 0)
	{
		ft_cd(cmd_tab, env);
		return (1);
	}
	else if (ft_strcmp(cmd, "echo") == 0)
	{
		ft_echo(cmd_tab);
		return (1);
	}
	else if (ft_strcmp(cmd, "pwd") == 0)
	{
		ft_pwd(cmd_tab);
		return (1);
	}
	if (ft_find_builtin2(cmd, cmd_tab, env) == 1)
		return (1);
	return (0);
}
