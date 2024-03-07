/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:38:07 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/07 16:22:32 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_builtin(char **arg, char ***env, int *exit_flag, t_tree *tree)
{
	int	check;
	check = 0;
	int		fd_stdout;
	int		fd_out_saved;

	if (tree->lst_exec->fd_in == -1 || tree->lst_exec->fd_out == -1)
	{
		printf("fd in = %d\nfd out = %d\n", tree->lst_exec->fd_in, tree->lst_exec->fd_out);
		ft_putstr_fd("file in doesn't exist\n", 2);
		return (2);
	}
	fd_stdout = dup(0);
	fd_out_saved = dup(1);
	dup2(tree->lst_exec->fd_in, 0);
	if (tree->lst_exec->fd_in > 2)
		close (tree->lst_exec->fd_in);
	dup2(tree->lst_exec->fd_out, 1);
	if (tree->lst_exec->fd_in > 2)
		close (tree->lst_exec->fd_out);
	check = ft_find_builtin(arg[0], arg, env, exit_flag);
	dup2(fd_stdout, 0);
	// if (fd_stdout >= 0)
	close(fd_stdout);
	dup2(fd_out_saved, 1);
	// if (fd_out_saved >= 0)
	close(fd_out_saved);
	return (check);
}

void	ft_child(t_tree *tree, char ***env, int status, int *tab_pid)
{
	char	**arg;

	arg = NULL;
	arg = ft_new_args(tree->lst_exec, status, *env);
	dup2(tree->lst_exec->fd_in, 0);
	dup2(tree->lst_exec->fd_out, 1);
	free_and_close_tree(tree);
	free(tab_pid);
	rl_clear_history();
	if (find_cmd(env, arg) == ERROR_MALLOC)
	{
		free_tab_tab(arg);
		exit (3);
	}
}

int	ft_exec_cmd_fork(t_tree *tree, char ***env, int status, t_tab_pid pid_data)
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
		ft_child(tree, env, status, pid_data.tab_pid);
	else
	{
		pid_data.tab_pid[pid_data.index++] = pid;
		g_exit_status = -100;
		if (tree->lst_exec->fd_out > 2)
			close(tree->lst_exec->fd_out);
		if (tree->lst_exec->fd_in > 2)
			close(tree->lst_exec->fd_in);
	}
	return (tmp);
}
