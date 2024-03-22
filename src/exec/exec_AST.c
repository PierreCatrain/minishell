/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_AST.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 01:19:42 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/22 16:57:34 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset_path(char **path)
{
	static int	free_path;

	free_path = 0;
	if (free_path++ == 0)
		free(*path);
	return (0);
}

int	builtin_exec(char ***env, t_tree *tree, int *status)
{
	int		exit_flag;
	char	**arg;
	int		old_status;

	exit_flag = -1;
	ft_replace_last_command(env, tree->lst_exec->args);
	arg = ft_new_args(tree->lst_exec, *status, *env);
	old_status = *status;
	*status = ft_exec_builtin(arg, env, &exit_flag, tree);
	if (exit_flag == 1 || *status == ERROR_MALLOC)
	{
		free_tab_tab(arg);
		free_and_close_tree(tree);
		free_tab_tab(*env);
		rl_clear_history();
		write(1, "exit\n", 5);
		exit(*status);
	}
	free_tab_tab(arg);
	if (exit_flag == 0 && old_status != 0)
		*status = old_status;
	return (*status);
}

int	fork_exec(t_tree *tree, char ***env, int *status, t_tab_pid *pid)
{
	while (tree->lst_exec != NULL)
	{
		if (ft_exec_cmd_fork(tree, env, *status, *pid) == ERROR_MALLOC)
			return (ERROR_MALLOC);
		ft_replace_last_command(env, tree->lst_exec->args);
		if (tree->lst_exec->next != NULL)
			tree->lst_exec = tree->lst_exec->next;
		else
			break ;
		(*pid).index++;
	}
	return (0);
}



void	wait_pid_status(int *ll_len, int *status, t_tab_pid *pid)
{
	while ((--(*ll_len)) + 1 > 0)
	{
	
		waitpid(pid->tab_pid[(pid->index)++], status, 0);
		if (WIFEXITED(*status))
			*status = WEXITSTATUS(*status);
	}
	free(pid->tab_pid);
	if ((g_signal == 130 || g_signal == 131))
		*status = g_signal;
}

int	ft_tree_exec(t_tree *tree, char ***env, int *status)
{
	int			ll_len;
	char		**arg;
	t_tab_pid	pid;

	arg = NULL;
	if (tree->left_child)
		ft_tree_exec(tree->left_child, env, status);
	if (tree->type == OPPERATOR_AND && *status == 0)
		ft_tree_exec(tree->right_child, env, status);
	if (tree->type == OPPERATOR_OR && *status != 0)
		ft_tree_exec(tree->right_child, env, status);
	if (tree->type == EXEC_LIST)
	{
		ll_len = ft_linked_list_size(tree->lst_exec);
		if (ll_len == 1 && ft_is_builtin(tree->lst_exec->args) == 1)
			return (builtin_exec(env, tree, status));
		pid.tab_pid = malloc(sizeof(int) * ll_len);
		pid.index = 0;
		if (fork_exec(tree, env, status, &pid) == ERROR_MALLOC)
			return (ERROR_MALLOC);
		pid.index = 0;
		wait_pid_status(&ll_len, status, &pid);
	}
	return (*status);
}

// echo ">"Wer''1234'$USER'"$USER""%USER"""