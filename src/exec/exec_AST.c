/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_AST.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 01:19:42 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/02 14:34:33 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_tree_exec(t_tree *tree, char ***env, int *status)
{
	t_tree	*tmp_tree;
	int		ll_len;
	int		status2;
	char	**arg;
	int		exit_flag;

	ll_len = 0;
	tmp_tree = tree;
	if (tmp_tree->left_child)
		ft_tree_exec(tmp_tree->left_child, env, status);
	if (tmp_tree->type == OPPERATOR_AND && *status == 0)
		ft_tree_exec(tmp_tree->right_child, env, status);
	if (tmp_tree->type == OPPERATOR_OR && *status != 0)
		ft_tree_exec(tmp_tree->right_child, env, status);
	if (tmp_tree->type == EXEC_LIST)
	{
		exit_flag = 0;
		ll_len = ft_linked_list_size(tmp_tree->lst_exec);
		if (ll_len == 1 && ft_is_builtin(tmp_tree->lst_exec->args[0]) == 1)
		{
			arg = ft_new_args(tmp_tree->lst_exec);
			status2 = ft_find_builtin(arg[0], arg, env, &exit_flag);
			if (exit_flag)
			{
				free_tab_tab(arg);
				free_and_close_tree(tmp_tree);
				exit(status2);
			}
			free_tab_tab(arg);
			return (status2);
		}
		while (tmp_tree->lst_exec != NULL)
		{
			arg = ft_new_args(tmp_tree->lst_exec);
			status2 = ft_exec_cmd_fork(tmp_tree, env, arg);
			tmp_tree->lst_exec = tmp_tree->lst_exec->next;
		}
		free_tab_tab(arg);
		while ((--ll_len) + 1 > 0)
			waitpid(0, status, 0);
	}
	if (WIFEXITED(*status))
		return (WEXITSTATUS(*status));
	return (0);
}
