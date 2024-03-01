/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:38:07 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/01 11:54:51 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

// recois une liste chaine si la liste en plus grande que 1, alors il y a des pipes et donc faire 
// la fonction qui

int	ft_exec_cmd_fork(t_tree *tree, char ***env, char **args)
{
	pid_t	pid;
	char	**arg;
	int		tmp;

	if (tree->lst_exec->fd_in == -1 || tree->lst_exec->fd_out == -1)
	{
		// gestion d'erreur
		return (2) ;
		// return (EXIT_FAILURE); est ce que reurn un exit failure a une utilite ?
	}
	tmp = g_exit_status;
	pid = fork();
	if (pid == -1)
	{
		return (EXIT_FAILURE);
		// gestion d'err
	}
	if (pid == 0)
	{
		arg = ft_new_args(tree->lst_exec); // a quoi ca sert ?
		dup2(tree->lst_exec->fd_in, 0);
		dup2(tree->lst_exec->fd_out, 1);
		free_and_close_tree(tree);
		free_tab_tab(args);
		find_cmd(env, arg);
	}
	else
	{
		g_exit_status = -100;
		if (tree->lst_exec->fd_out > 2)
			close(tree->lst_exec->fd_out);
		if (tree->lst_exec->fd_in > 2)
			close(tree->lst_exec->fd_in);
	}
	return (tmp);
}

// int	main(int ac, char **av, char **env)
// {
// 	(void)ac;
// 	printf("%d\n", ft_exec_cmd_fork(0, 1, av + 1, env));
// }