/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_complete_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 04:18:52 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/19 05:35:57 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int ft_add_left_child(t_tree **tree, t_tree *new)
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

int ft_add_right_child(t_tree **tree, t_tree *new)
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

t_tree *ft_tree_new(int type)
{
    t_tree *new;

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

int ft_complete_tree(t_tree **tree, t_lst_exec **lst_exec, t_token *token)
{
    lst_exec = (t_lst_exec **)lst_exec;
    tree = (t_tree **)tree;
    token = (t_token *)token;
    
    return (SUCCESS);
}