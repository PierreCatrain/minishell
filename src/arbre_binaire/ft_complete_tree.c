/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_complete_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 04:18:52 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/22 18:41:46 by picatrai         ###   ########.fr       */
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

t_token *before_token(t_token *token)
{
    t_token *new;
    t_token *tmp;

    tmp = token;
    while (tmp->prev != NULL)
        tmp = tmp->prev;
    new = tmp;
    while (new->next != token)
        new = new->next;
    new->next = NULL;
    while (new->prev != NULL)
        new = new->prev;
    return (new);
}

t_token *after_token(t_token *token)
{
    t_token *new;

    new = token->next;
    new->prev = NULL;
    return (new);
}

int ft_is_there_parenthesis(t_token *token)
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

t_token *without_parenthesis(t_token *token)
{
    t_token *new;
    
    while (token->prev != NULL)
        token = token->prev;
    new = token->next;
    new->prev = NULL;
    while (new->next->next != NULL)
        new = new->next;
    new->next = NULL;
    while (new->prev != NULL)
        new = new->prev;
    return (new);
}

t_tree *ft_first_empty_child(t_tree *tree)
{
    t_tree *res;

    if (tree == NULL)
        return (NULL);
    if (tree->type == EXEC_LIST)
        return (NULL);
    if (tree->left_child != NULL)
    {
        res = ft_first_empty_child(tree->left_child);
        if (res != NULL)
            return (res);
    }
    if (tree->right_child != NULL)
    {
        res = ft_first_empty_child(tree->right_child);
        if (res != NULL)
            return (res);
    }
    if ((tree->left_child == NULL || tree->right_child == NULL) && tree->type != EXEC_LIST)
        return (tree);
    return (NULL);
}

int ft_add_tree(t_tree **tree, t_tree *new, t_token *token, int add)
{
    *tree = ft_first_empty_child(*tree);
    if (*tree == NULL)
    {
        if (ft_add_left_child(tree, new) == ERROR_MALLOC)
            return (ERROR_MALLOC);
        if (add == ADD)
        {
            if (ft_lst_exec(token, &(*tree)->lst_exec) != SUCCESS)
                return (ERROR);
        }
    }
    else if ((*tree)->left_child == NULL)
    {
        if (ft_add_left_child(tree, new) == ERROR_MALLOC)
            return (ERROR_MALLOC);
        if (add == ADD)
        {
            if (ft_lst_exec(token, &(*tree)->left_child->lst_exec) != SUCCESS)
                return (ERROR);
        }
    }
    else if ((*tree)->right_child == NULL)
    {
        if (ft_add_right_child(tree, new) == ERROR_MALLOC)
            return (ERROR_MALLOC);
        if (add == ADD)
        {
            if (ft_lst_exec(token, &(*tree)->right_child->lst_exec) != SUCCESS)
                return (ERROR);
        }
    }
    while ((*tree)->parent != NULL)
        *tree = (*tree)->parent;
    return (SUCCESS);
}

int ft_complete_tree(t_tree **tree, t_token *token)
{
    t_token *tmp;
    int parenthesis_open;

    tmp = token;
    parenthesis_open = 0;
    while (token != NULL)
    {
        if (parenthesis_open == 0 && (token->type == AND || token->type == OR))
            break;
        if (token->type == OPEN_PARENTHESIS)
            parenthesis_open++;
        if (token->type == CLOSE_PARENTHESIS)
            parenthesis_open--;
        token = token->next;
    }
    if (token != NULL)
    {
        if (parenthesis_open == 0 && (token->type == AND || token->type == OR))
        {
            if (token->type == AND)
                ft_add_tree(tree, ft_tree_new(OPPERATOR_AND), tmp, DONT_ADD);
            else if (token->type == OR)
                ft_add_tree(tree, ft_tree_new(OPPERATOR_OR), tmp, DONT_ADD);
            ft_complete_tree(tree, before_token(token));
            ft_complete_tree(tree, after_token(token));
            ft_free_token(&token);
        }
    }
    else if (ft_is_there_parenthesis(tmp) == 1)
    {
        ft_complete_tree(tree, without_parenthesis(tmp));
        //ft_free_token(&tmp);
    }
    else
        ft_add_tree(tree, ft_tree_new(EXEC_LIST), tmp, ADD);
    return (SUCCESS);
}