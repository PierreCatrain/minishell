/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 22:48:14 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/04 18:12:22 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_mini_expand(t_expand *expand)
{
	t_expand *tmp;
	
	while (expand != NULL)
	{
		tmp = expand;
		expand = expand->next;
		free(tmp);
	}
}

void free_expand(t_expand **expand, int len)
{
	t_expand *tmp;
	int index;

	index = 0;
	while (index < len)
	{
		while (expand[index] != NULL)
		{
			tmp = expand[index];
			expand[index] = expand[index]->next;
			free(tmp);
		}
		index++;
	}
	free(expand);
}

void	free_close_exec_list(t_lst_exec *exec)
{
	t_lst_exec	*tmp;

	while (exec->prev != NULL)
		exec = exec->prev;
	while (exec != NULL)
	{
		tmp = exec;
		free_expand(exec->expand, ft_strlen_2d(exec->args));
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

// void	ft_free_tab_tab_incremented(char **tab)
// {
// 	int	i;

// 	i = -1;
// 	while (tab[++i])
// 		free(tab[i]);
// }

void	ft_free_wildcard(t_wildcard **ls)
{
	t_wildcard	*tmp;

	while ((*ls)->prev != NULL)
		*ls = (*ls)->prev;
	while (*ls != NULL)
	{
		tmp = *ls;
		*ls = (*ls)->next;
		free(tmp->str);
		free(tmp);
	}
}

void	ft_free_pipes(int **fd_pipes, int nb_pipes)
{
	while (--nb_pipes >= 0)
	{
		free(fd_pipes[nb_pipes]);
	}
	free(fd_pipes);
}
