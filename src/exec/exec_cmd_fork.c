/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:38:07 by lgarfi            #+#    #+#             */
/*   Updated: 2024/02/09 17:46:19 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

// recois une liste chaine si la liste en plus grande que 1, alors il y a des pipes et donc faire 
// la fonction qui
int	ft_exec_cmd_fork(t_tree *tree, char **env)
{
	pid_t	pid;
	int		status;

	if (tree->lst_exec->fd_in == -1 || tree->lst_exec->fd_out == -1)
	{
		// gestion d'erreur
		return (EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		printf("bash: err:%d (fork)", errno);
		return (EXIT_FAILURE);
		// gestion d'err
	}
	if (pid == 0)
	{
		dup2(tree->lst_exec->fd_in, 0);
		dup2(tree->lst_exec->fd_out, 1);
		find_cmd(env, tree->lst_exec->args);
	}
	else
	{
		waitpid(0, &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
	}
	return (g_exit_status);
}

// int	main(int ac, char **av, char **env)
// {
// 	(void)ac;
// 	printf("%d\n", ft_exec_cmd_fork(0, 1, av + 1, env));
// }