/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_and_check_cmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 10:10:03 by lgarfi            #+#    #+#             */
/*   Updated: 2024/02/29 17:35:28 by lgarfi           ###   ########.fr       */
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

// void	ft_exec_env_less(char **cmd)
// {
// 	char	*final_cmd;
	
// 	final_cmd = ft_strjoin_path_without_free("/usr/bin", cmd[0]);
// 	if (access(final_cmd, F_OK | X_OK) == 0)
// 	{
// 		if (execve(final_cmd, cmd, NULL) == -1)
// 		{
// 			printf("bash: %s: cannot execute binary file: %s\n", cmd[0], strerror(errno));
// 			free(final_cmd);
// 			free_tab_tab(cmd);
// 			exit(126);
// 		}
// 	}
// 	else
// 	{
// 		printf("bash: %s: %s\n", cmd[0], strerror(errno));
// 		free(final_cmd);
// 		free_tab_tab(cmd);
// 		exit(126);
// 	}
// }

int	ft_check_path_cmd(char **env, char **cmd)
{
	int		i;
	char	*cmd_path;
	char	**path_split;
	char	*msg_err;

	i = -1;
	path_split = ft_get_path_cmd();
	if (!path_split)
	{
		exit (127);
		// ft_exec_env_less(cmd);
	}
	while (path_split[++i])
	{
		cmd_path = ft_strjoin_path(path_split[i], cmd[0]);
		if (cmd_path == NULL)
		{
			return (1);
		}
		if (!access(cmd_path, F_OK | X_OK))
		{
			if (execve(cmd_path, cmd, env) == -1)
			{
				printf("bash: %s: cannot execute binary file: %s\n", cmd[0], strerror(errno));
				free(cmd_path);
				free_tab_tab(cmd);
				exit (126);
			}
		}
		free (cmd_path);
	}
	msg_err = ft_strjoin_wihtout_free(cmd[0], ": command not found\n");
	ft_putstr_fd(msg_err, 2);
	free (msg_err);
	free_tab_tab(cmd);
	free_tab_tab(env);
	free(path_split);
	exit(127);
}

int	find_cmd(char ***env, char **cmd)
{
	int	status;
	int	fake_exit_status; // on s'en fiche de celui car on ne l'exit pas

	status = 0;
	if (ft_is_builtin(cmd[0]))
	{
		status = ft_find_builtin(cmd[0], cmd, env, &fake_exit_status);// access chemin absolue //EXECUTE BUILTIN
		if (status == -1)
			return (1);
		exit(status);
	}
	else
	{
		if (access(cmd[0], F_OK | X_OK) == 0) // mettre les droits d'exec et de lecture
		{
			if (execve(cmd[0], cmd, *env) == -1)
			{
				printf("bash: %s: cannot execute binary file: %s\n", cmd[0], strerror(errno));
				exit (126);
			}
		}
		ft_check_path_cmd(*env, cmd);
	}
	return (status);
}
