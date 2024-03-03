/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_and_check_cmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 10:10:03 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/03 13:00:27 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_get_path_cmd(void)
{
	char	**path_split;
	char	*path;

	path = getenv("PATH");
	if (!path)
	{
		printf("PATH n'existe pas dans env\n");
		return (NULL);
	}
	path_split = ft_split(path, ':');
	if (!path_split)
	{
		printf("error prblm\n");
		return (NULL);
	}
	return (path_split);
}

void	ft_check_path_execve(char **path, char ***cmd, char ***env)
{
	if (execve(*path, *cmd, *env) == -1)
	{
		printf("bash: %s: cannot execute binary file: \
			%s\n", (*cmd)[0], strerror(errno));
		free(*path);
		free_tab_tab(*cmd);
		free_tab_tab(*env);
		exit (126);
	}
}

int	ft_check_path_cmd(char **env, char **cmd)
{
	int		i;
	char	*cmd_path;
	char	**path_split;
	char	*msg_err;

	path_split = ft_get_path_cmd();
	if (!path_split)
		exit (127);
	i = -1;
	while (path_split[++i])
	{
		cmd_path = ft_strjoin_path(path_split[i], cmd[0]);
		if (cmd_path == NULL)
			return (ERROR_MALLOC);
		if (!access(cmd_path, F_OK | X_OK))
			ft_check_path_execve(&cmd_path, &cmd, &env);
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

// access chemin absolue //EXECUTE BUILTIN
int	find_cmd(char ***env, char **cmd)
{
	int	status;
	int	fake_exit_status;

	status = 0;
	if (ft_is_builtin(cmd[0]))
	{
		status = ft_find_builtin(cmd[0], cmd, env, &fake_exit_status);
		if (status == -1)
			return (1);
		exit(status);
	}
	else
	{
		if (access(cmd[0], F_OK | X_OK) == 0)
		{
			if (execve(cmd[0], cmd, *env) == -1)
			{
				printf("bash: %s: cannot execute binary file: \
				%s\n", cmd[0], strerror(errno));
				exit (126);
			}
		}
		ft_check_path_cmd(*env, cmd);
	}
	return (status);
}
