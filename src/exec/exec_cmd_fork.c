/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:38:07 by lgarfi            #+#    #+#             */
/*   Updated: 2024/01/31 01:24:22 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	ft_exec_cmd_fork(int fd_in, int fd_out, char **cmd, char **env)
{
	pid_t pid;

	if (fd_in == -1 || fd_out == -1)
	{
		// gestion d'erreur
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		printf("bash: err:%d (fork)", errno);
		return ;
	}
	if (pid == 0)
	{
		dup2(fd_in, 0);
		dup2(fd_out, 1);
		find_cmd(env, cmd);
	}
	else
		waitpid(0, NULL, 0);
}

// int	main(int ac, char **av, char **env)
// {
// 	(void)ac;
// 	ft_exec_cmd_fork(0, 1, av + 1, env);
// }