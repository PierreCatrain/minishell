/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 22:48:14 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/01 21:54:38 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_close_exec_list(t_lst_exec *exec)
{
	t_lst_exec	*tmp;

	while (exec->prev != NULL)
	{
		exec = exec->prev;
	}	
	while (exec != NULL)
	{
		tmp = exec;
		free_2d(exec->args);
		if (exec->fd_in > 2)
			close(exec->fd_in);
		if (exec->fd_out > 2)
			close(exec->fd_out);
		exec = exec->next;
		free(tmp);
	}
}

void	free_close_tree(t_tree *tree)
{
	if (tree->left_child != NULL)
		free_close_tree(tree->left_child);
	if (tree->right_child != NULL)
		free_close_tree(tree->right_child);
	if (tree->lst_exec != NULL)
		free_close_exec_list(tree->lst_exec);
	free(tree);
	return ;
}

void	free_and_close_tree(t_tree *tree)
{
	if (tree == NULL)
		return ;
	while (tree->parent != NULL)
		tree = tree->parent;
	free_close_tree(tree);
}

void	free_tab_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

void	ft_free_tab_tab_incremented(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
}
