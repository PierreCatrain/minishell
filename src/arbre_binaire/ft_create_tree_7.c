/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_tree_7.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 04:21:19 by picatrai          #+#    #+#             */
/*   Updated: 2024/02/11 04:05:56 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_is_there_parenthesis(t_token *token)
{
	while (token->prev != NULL)
		token = token->prev;
	if (token->type != OPEN_PARENTHESIS)
		return (0);
	while (token->next != NULL)
		token = token->next;
	if (token->type != CLOSE_PARENTHESIS)
		return (0);
	return (1);
}

t_token	*without_parenthesis(t_token *token)
{
	t_token	*new;
	t_token	*tmp;

	while (token->prev != NULL)
		token = token->prev;
	tmp = token->next;
	new = NULL;
	while (tmp->next != NULL)
	{
		if (ft_lst_add_back(&new, ft_lstnew_no_malloc(tmp->str, \
						tmp->quotes, tmp->type)) == ERROR_MALLOC)
			return (NULL);
		tmp = tmp->next;
	}
	while (new->prev != NULL)
		new = new->prev;
	return (new);
}

t_tree	*ft_first_empty_child(t_tree *tree)
{
	t_tree	*res;

	if (tree == NULL)
		return (NULL);
	if (tree->type == EXEC_LIST)
		return (NULL);
	if (tree->right_child != NULL)
	{
		res = ft_first_empty_child(tree->right_child);
		if (res != NULL)
			return (res);
	}
	if (tree->left_child != NULL)
	{
		res = ft_first_empty_child(tree->left_child);
		if (res != NULL)
			return (res);
	}
	if ((tree->left_child == NULL || tree->right_child == NULL) \
			&& tree->type != EXEC_LIST)
		return (tree);
	return (NULL);
}

int	ft_add_tree_null(t_tree **tree, t_tree *new, t_token *token, t_data_parse *data_parse)
{
	if (ft_add_left_child(tree, new) == ERROR_MALLOC)
		return (ft_print_error_malloc(), ERROR_MALLOC);
	if ((*tree)->type == EXEC_LIST)
	{
		if (ft_lst_exec(token, &(*tree)->lst_exec, data_parse) != SUCCESS)
			return (ERROR);
	}
	return (SUCCESS);
}

int	ft_add_tree_no_null(t_tree **tree, t_tree *new, t_token *token, t_data_parse *data_parse)
{
	if ((*tree)->right_child == NULL)
	{
		if (ft_add_right_child(tree, new) == ERROR_MALLOC)
			return (ft_print_error_malloc(), ERROR_MALLOC);
		if ((*tree)->right_child->type == EXEC_LIST)
		{
			if (ft_lst_exec(token, &(*tree)->right_child->lst_exec, data_parse) != SUCCESS)
				return (ERROR);
		}
	}
	else if ((*tree)->left_child == NULL)
	{
		if (ft_add_left_child(tree, new) == ERROR_MALLOC)
			return (ft_print_error_malloc(), ERROR_MALLOC);
		if ((*tree)->left_child->type == EXEC_LIST)
		{
			if (ft_lst_exec(token, &(*tree)->left_child->lst_exec, data_parse) != SUCCESS)
				return (ERROR);
		}
	}
	return (SUCCESS);
}
