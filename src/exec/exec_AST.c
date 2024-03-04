/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_AST.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 01:19:42 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/04 08:25:48 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_tree_exec(t_tree *tree, char ***env, int *status)
{
	int		ll_len;
	int		status2;
	char	**arg;
	int		exit_flag;

	ll_len = 0;
	arg = NULL;
	if (tree->left_child)
		ft_tree_exec(tree->left_child, env, status);
	if (tree->type == OPPERATOR_AND && *status == 0)
		ft_tree_exec(tree->right_child, env, status);
	if (tree->type == OPPERATOR_OR && *status != 0)
		ft_tree_exec(tree->right_child, env, status);
	if (tree->type == EXEC_LIST)
	{
		exit_flag = 0;
		ll_len = ft_linked_list_size(tree->lst_exec);
		if (ll_len == 1 && ft_is_builtin(tree->lst_exec->args[0]) == 1)
		{
			arg = ft_new_args(tree->lst_exec);
			status2 = ft_find_builtin(arg[0], arg, env, &exit_flag);
			if (exit_flag || status2 == ERROR_MALLOC)
			{
				free_tab_tab(arg);
				free_and_close_tree(tree);
				free_tab_tab(*env);
				rl_clear_history();
				exit(status2);
			}
			return (free_tab_tab(arg), status2);
		}
		while (tree->lst_exec != NULL)
		{
			status2 = ft_exec_cmd_fork(tree, env);
			if (status2 == ERROR_MALLOC)
				return (ERROR_MALLOC);
			if (tree->lst_exec->next != NULL)
				tree->lst_exec = tree->lst_exec->next;
			else
				break ;
		}
		while ((--ll_len) + 1 > 0)
			waitpid(0, status, 0);
	}
	if (WIFEXITED(*status))
		return (WEXITSTATUS(*status));
	return (0);
}
