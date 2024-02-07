/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:38:07 by lgarfi            #+#    #+#             */
/*   Updated: 2024/02/07 21:08:16 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	ft_exec_cmd_fork(t_tree *tree, char **env)
{
	t_exec	exec;

	exec.exit_status = 0;
	if (tree->lst_exec->fd_in == -1 || tree->lst_exec->fd_out == -1)
	{
		// gestion d'erreur
		return (2);
	}
	exec.pid = fork();
	if (exec.pid == -1)
	{
		printf("bash: err:%d (fork)", errno);
		return (2);
	}
	if (exec.pid == 0)
	{
		dup2(tree->lst_exec->fd_in, 0);
		dup2(tree->lst_exec->fd_out, 1);
		find_cmd(env, tree->lst_exec->cmd);
	}
	else
	{
		waitpid(0, &exec.status, 0);
		if (WIFEXITED(exec.status))
			exec.exit_status = WEXITSTATUS(exec.status);
	}
	return (exec.exit_status);
}

// int	main(int ac, char **av, char **env)
// {
// 	(void)ac;
// 	printf("%d\n", ft_exec_cmd_fork(0, 1, av + 1, env));
// }