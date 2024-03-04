/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_tree_6.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 04:16:21 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/04 11:59:42 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*ft_lstnew_no_malloc(char *str, int quotes, int type, t_expand *expand)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->str = ft_strdup(str);
	if (new->str == NULL)
		return (free(new), NULL);
	new->quotes = quotes;
	new->expand = expand;
	new->type = type;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

int	ft_add_left_child(t_tree **tree, t_tree *new)
{
	if (new == NULL)
		return (ERROR_MALLOC);
	else if (*tree == NULL)
	{
		*tree = new;
		return (SUCCESS);
	}
	new->parent = *tree;
	(*tree)->left_child = new;
	return (SUCCESS);
}

int	ft_add_right_child(t_tree **tree, t_tree *new)
{
	if (new == NULL)
		return (ERROR_MALLOC);
	else if (*tree == NULL)
	{
		*tree = new;
		return (SUCCESS);
	}
	new->parent = *tree;
	(*tree)->right_child = new;
	return (SUCCESS);
}

t_tree	*ft_tree_new(int type)
{
	t_tree	*new;

	new = malloc (sizeof(t_tree));
	if (new == NULL)
		return (NULL);
	new->type = type;
	new->parent = NULL;
	new->left_child = NULL;
	new->right_child = NULL;
	new->lst_exec = NULL;
	return (new);
}

t_token	*before_token(t_token *token)
{
	t_token	*new;
	t_token	*tmp;

	new = NULL;
	tmp = token;
	while (tmp->prev != NULL)
		tmp = tmp->prev;
	while (tmp != token)
	{
		if (ft_lst_add_back(&new, ft_lstnew_no_malloc(tmp->str, \
						tmp->quotes, tmp->type, tmp->expand)) == ERROR_MALLOC)
			return (NULL);
		tmp = tmp->next;
	}
	while (new->prev != NULL)
		new = new->prev;
	return (new);
}

t_token	*after_token(t_token *token)
{
	t_token	*new;
	t_token	*tmp;

	new = NULL;
	tmp = token->next;
	while (tmp != NULL)
	{
		if (ft_lst_add_back(&new, ft_lstnew_no_malloc(tmp->str, \
						tmp->quotes, tmp->type, tmp->expand)) == ERROR_MALLOC)
			return (NULL);
		tmp = tmp->next;
	}
	while (new->prev != NULL)
		new = new->prev;
	return (new);
}
