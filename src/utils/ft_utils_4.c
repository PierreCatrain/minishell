/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 05:46:43 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/22 17:24:29 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void ft_printf_2d(char **str)
{
    int index;

    printf("args-> ");
    index = 0;
    while (str[index])
    {
        printf("%s ", str[index]);
        index++;
    }
    printf("\n");
}

void	ft_print_lst_exec(t_lst_exec *lst_exec)
{
    printf("exec\n");
    while (lst_exec != NULL)
	{
	    printf("\ncmd -> %s\n", lst_exec->cmd);
		ft_printf_2d(lst_exec->args);
	    printf("in  -> %d\n", lst_exec->fd_in);
	    printf("out -> %d\n\n", lst_exec->fd_out);
		lst_exec = lst_exec->next;
	}
}

void    ft_print_tree(t_tree *tree)
{
    if (tree == NULL)
        return ;
    if (tree->type == EXEC_LIST)
    {
        ft_print_lst_exec(tree->lst_exec);
    }
    else if (tree->type == OPPERATOR_AND)
    {
        printf("AND\n");
    }
    else if (tree->type == OPPERATOR_OR)
    {
        printf("OR\n");
    }
    if (tree->left_child != NULL)
        ft_print_tree(tree->left_child);
    if (tree->right_child != NULL)
        ft_print_tree(tree->right_child);
    return ;
}

void    ft_free_2d_index(char **str, int index)
{
    while (--index)
        free(str[index]);
    free(str);
}

int ft_strlen_2d(char **str)
{
    int index;
    
    if (str == NULL)
        return (0);
    index = 0;
    while (str[index])
        index++;
    return (index);
}

char **ft_join_2d(char **args_cmd, char *str)
{
    char **new;
    int index;

    new = malloc((ft_strlen_2d(args_cmd) + 2) * sizeof(char *));
    if (new == NULL)
        return (free_2d(args_cmd), NULL);
    if (args_cmd == NULL)
    {
        index = 0;
        new[index] = ft_strdup(str);
        if (new[index] == NULL)
            return (free(new), NULL);
        new[++index] = NULL;
        return (new);
    }
    index = -1;
    while (args_cmd[++index])
    {
        new[index] = ft_strdup(args_cmd[index]);
        if (new[index] == NULL)
            return (ft_free_2d_index(new, index), free_2d(args_cmd), NULL);
    }
    new[index] = ft_strdup(str);
    if (new[index] == NULL)
        return (ft_free_2d_index(new, index), free_2d(args_cmd), NULL);
    new[++index] = NULL;
    return (free_2d(args_cmd), new);
}