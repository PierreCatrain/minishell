/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 09:32:17 by lgarfi            #+#    #+#             */
/*   Updated: 2024/01/29 07:51:35 by lgarfi           ###   ########.fr       */
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

int	ft_find_builtin(char *str, char **path_tab, char **env)
{
	if (ft_strcmp(str, "cd") == 0)
		ft_cd(path_tab, env);
	else if (ft_strcmp(str, "echo") == 0)
		ft_echo(path_tab);
	else if (ft_strcmp(str, "pwd") == 0)
		ft_pwd(path_tab);
	else if (ft_strcmp(str, "exit") == 0)
		ft_exit(path_tab);
	else if (ft_strcmp(str, "unset") == 0) 
		ft_unset(env, path_tab[1]); // a modifier pour pouvoir faire plusieurs unset
	else if (ft_strcmp(str, "export") == 0)
		ft_export(env, path_tab[1]); // pareil
	else if (ft_strcmp(str, "env") == 0)
		ft_env(env);
	return (0);
}
