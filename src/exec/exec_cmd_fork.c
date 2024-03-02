/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:38:07 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/02 14:54:17 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_child(t_tree *tree, char ***env, char **args)
{
	dup2(tree->lst_exec->fd_in, 0);
	dup2(tree->lst_exec->fd_out, 1);
	free_and_close_tree(tree);
	find_cmd(env, args);
}

int	ft_exec_cmd_fork(t_tree *tree, char ***env, char **args)
{
	pid_t	pid;
	int		tmp;

	if (tree->lst_exec->fd_in == -1 || tree->lst_exec->fd_out == -1)
	{
		return (2);
	}
	tmp = g_exit_status;
	pid = fork();
	if (pid == -1)
	{
		return (EXIT_FAILURE);
	}
	if (pid == 0)
		ft_child(tree, env, args);
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
