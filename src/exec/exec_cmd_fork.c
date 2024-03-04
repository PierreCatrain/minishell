/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:38:07 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/04 18:41:53 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_child(t_tree *tree, char ***env, int status)
{
	char	**arg;

	arg = NULL;
	arg = ft_new_args(tree->lst_exec, status, *env);
	dup2(tree->lst_exec->fd_in, 0);
	dup2(tree->lst_exec->fd_out, 1);
	free_and_close_tree(tree);
	rl_clear_history();
	if (find_cmd(env, arg) == ERROR_MALLOC)
	{
		free_tab_tab(arg);
		exit (3);
	}
}

int	ft_exec_cmd_fork(t_tree *tree, char ***env, int status, int *tab_pid, int i)
{
	pid_t	pid;
	int		tmp;

	if (tree->lst_exec->fd_in == -1 || tree->lst_exec->fd_out == -1)
	{
		ft_putstr_fd("file ine doesn't exist\n", 2);
		return (2);
	}
	tmp = g_exit_status;
	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	if (pid == 0)
		ft_child(tree, env, status);
	else
	{
		tab_pid[i++] = pid;
		g_exit_status = -100;
		if (tree->lst_exec->fd_out > 2)
			close(tree->lst_exec->fd_out);
		if (tree->lst_exec->fd_in > 2)
			close(tree->lst_exec->fd_in);
	}
	return (tmp);
}
