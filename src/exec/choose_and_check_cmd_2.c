/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_and_check_cmd_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 23:48:10 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/09 23:50:10 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_cmd_2(char **cmd, int *status, char ***env)
{
	int	fake_exit_status;

	fake_exit_status = 0;
	*status = ft_find_builtin(cmd[0], cmd, env, &fake_exit_status);
	if (*status == -1)
		return (1);
	free_tab_tab(cmd);
	free_tab_tab(*env);
	exit(*status);
}

int	find_cmd(char ***env, char **cmd)
{
	int	status;

	status = 0;
	if (ft_is_builtin(cmd[0]))
	{
		find_cmd_2(cmd, &status, env);
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
		ft_check_path_cmd(env, cmd);
	}
	return (status);
}
