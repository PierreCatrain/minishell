/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 10:10:03 by lgarfi            #+#    #+#             */
/*   Updated: 2024/01/30 19:13:31 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	ft_execve_cmd(char **cmd, char **path_split, char **env)
{
	int	i;
	char	*cmd_path;

	i = -1;
	while (path_split[++i])
	{
		cmd_path = ft_strjoin_path(path_split[i], cmd[0]);
		if (cmd_path == NULL)
		{
			return (1);
			// gestion d'erreur
		}
		if (!access(cmd_path, F_OK | X_OK))
		{
			print_tab_tab(cmd);
			if (execve(cmd_path, cmd, env) == -1)
			{
				return (2); // gestion d'erreur
			}
		}
		free (cmd_path);
	}
	free_tab_tab(path_split);
	free_tab_tab(cmd);
	return (1);
}

void	find_cmd(char **env, char **cmd)
{
	char	*path;
	char	**path_split;

	if (ft_find_builtin(cmd[0], cmd, cmd) == 1)
		return ;
	if (access(cmd[0], F_OK | X_OK) == 0)
	{
		printf("bonjour\n");
		execve(cmd[0], cmd, env);
	}
	path = getenv("PATH");
	if (!path)
	{
		printf("PATH n'existe pas dans env\n");
		return ; //gestion d'erreur;
	}
	path_split = ft_split(path, ':');
	if (!path_split)
	{
		printf("error prblm\n");
		return ;
		// gestion d'err
		// free path ?
	}
	printf("ici\n");
	ft_execve_cmd(cmd, path_split, env);
}

// void	ft_exec_cmd(char **env, char **cmd, int fd_in, int fd_out, int pipe_1, int pipe_2)
// {

// }

// int	main(int ac, char **av, char **env)
// {
// 	(void)ac;
// 	find_cmd(env, av + 1);
// }