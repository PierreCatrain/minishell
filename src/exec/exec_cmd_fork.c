/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:38:07 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/22 18:41:11 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_builtin(char **arg, char ***env, int *exit_flag, t_tree *tree)
{
	int		check;
	int		fd_in_saved;
	int		fd_out_saved;

	if (tree->lst_exec->fd_in == -1 || tree->lst_exec->fd_out == -1)
		return (ft_putstr_fd("minishell: File: Permission denied\n", 2), 1);
	if (tree->lst_exec->fd_in == -2)
		return (ft_putstr_fd("minishell: File:"
				" No such file or directory\n", 2), 1);
	fd_in_saved = dup(0);
	fd_out_saved = dup(1);
	dup2(tree->lst_exec->fd_in, 0);
	if (tree->lst_exec->fd_in > 2)
		close (tree->lst_exec->fd_in);
	dup2(tree->lst_exec->fd_out, 1);
	if (tree->lst_exec->fd_out > 2)
		close (tree->lst_exec->fd_out);
	check = ft_find_builtin(arg[0], arg, env, exit_flag);
	dup2(fd_in_saved, 0);
	close(fd_in_saved);
	dup2(fd_out_saved, 1);
	close(fd_out_saved);
	return (check);
}

void	ft_child_2(t_tree *tree, char ***env, int *tab_pid)
{
	if (tree->lst_exec->fd_in == -2)
	{
		ft_putstr_fd("minishell: File: No such file or directory\n", 2);
		free_and_close_tree(tree);
		free_tab_tab(*env);
		free(tab_pid);
		exit (1);
	}
	if (tree->lst_exec->fd_in == -1 || tree->lst_exec->fd_out == -1)
	{
		ft_putstr_fd("minishell: File: Permission denied\n", 2);
		free_and_close_tree(tree);
		free_tab_tab(*env);
		free(tab_pid);
		exit (1);
	}
	if (tree->lst_exec->args == NULL)
	{
		free_and_close_tree(tree);
		free_tab_tab(*env);
		free(tab_pid);
		exit (0);
	}
}

void	ft_child(t_tree *tree, char ***env, int status, int *tab_pid)
{
	char	**arg;

	ft_child_2(tree, env, tab_pid);
	arg = NULL;
	arg = ft_new_args(tree->lst_exec, status, *env);
	if (!arg)
	{
		free_and_close_tree(tree);
		free_tab_tab(*env);
		free(tab_pid);
		exit (0);
	}
	if (ft_strcmp("./minishell", arg[0]) == 0)//
	{//
		printf("trouver\n");
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		// if (ft_change_sig(3) != SUCCESS)
		// 	return ;
	}//
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

// void print(int signal)
// {
// 	(void)signal;
// 	printf("toto\n");
// 	g_signal = 130;
// }

int	ft_exec_cmd_fork(t_tree *tree, char ***env, int status, t_tab_pid pid_data)
{
	// struct sigaction	s_quit;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	if (pid == 0)
	{
		// signal(SIGINT, SIG_DFL);
		// signal(SIGQUIT, SIG_DFL);
		// signal(SIGQUIT, SIG_IGN);
		// if (ft_change_sig(1) != SUCCESS)
		// 	return (ERROR_MALLOC);
		// signal(SIGINT, SIG_IGN);
		// sigemptyset(&s_quit.sa_mask);
		// sigaddset(&s_quit.sa_mask, SIGQUIT);
		// s_quit.sa_flags = 0;
		// s_quit.sa_handler = &print;
		// if (sigaction(SIGQUIT, &s_quit, NULL) == -1)
		// {
		// 	ft_putstr_fd("minishell: error with sigaction\n", 2);
		// 	return (ERROR);
		// }
		ft_child(tree, env, status, pid_data.tab_pid);
	}
	else
	{
		pid_data.tab_pid[pid_data.index++] = pid;
		if (tree->lst_exec->fd_out > 2)
			close(tree->lst_exec->fd_out);
		if (tree->lst_exec->fd_in > 2)
			close(tree->lst_exec->fd_in);
	}
	return (SUCCESS);
}
