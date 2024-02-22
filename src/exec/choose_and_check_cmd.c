/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_and_check_cmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 10:10:03 by lgarfi            #+#    #+#             */
/*   Updated: 2024/02/22 19:29:35 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char	**ft_get_path_cmd(void)
{
	char	**path_split;
	char	*path;

	path = getenv("PATH"); // free ?
	if (!path)
	{
		printf("PATH n'existe pas dans env\n");
		return (NULL); //gestion d'erreur;
	}
	path_split = ft_split(path, ':');
	if (!path_split)
	{
		printf("error prblm\n");
		return (NULL);
		// gestion d'err
		// free path ?
	}
	return (path_split);
}

int	ft_check_path_cmd(char **env, char **cmd)
{
	int		i;
	char	*cmd_path;
	char	**path_split;
	char	*msg_err;

	i = -1;
	path_split = ft_get_path_cmd();
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
			if (execve(cmd_path, cmd, env) == -1)
				return (2);
		}
		free (cmd_path);
	}
	msg_err = ft_strjoin_wihtout_free(cmd[0], ": command not found\n");
	ft_putstr_fd(msg_err, 2);
	free (msg_err);
	exit(127);
}

int	find_cmd(char ***env, char **cmd)
{
	if (ft_find_builtin(cmd[0], cmd, env) == 1)// access chemin absolue
		return (1);
	if (access(cmd[0], F_OK | X_OK) == 0) // mettre les droits d'exec et de lecture
		execve(cmd[0], cmd, *env);
	ft_check_path_cmd(*env, cmd);
	return (0);
}

// int	main(int ac, char **av, char **envp)
// {
// 	(void)ac;
// 	(void)envp;
	
// 	char	*msg_err;

// 	msg_err = ft_get_err_msg(av[1], ": command not found\n");
// 	ft_putstr_fd(msg_err ,2);
// }
