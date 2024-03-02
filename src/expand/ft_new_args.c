/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 06:51:13 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/02 14:50:31 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char **ft_expand_step_1(t_lst_exec *lst_exec)
{
    int index;
    char **new_args;

    new_args = malloc ((ft_strlen_2d(lst_exec->args) + 1) * sizeof(char *));
    if (new_args == NULL)
        return (NULL);
    index = 0;
    while (index < lst_exec->len_expand)
    {
        new_args[index] = ft_replace_env_variable(lst_exec->args[index], lst_exec->expand[index]);
        if (new_args[index] == NULL)
            return (NULL);
        index++;
    }
    new_args[index] = NULL;
    return (new_args);
}

char **ft_expand_step_2(t_lst_exec *lst_exec, char **args, t_wildcard *ls)
{
    int index;
    char **new_args;

    new_args = malloc (sizeof(char *));
    if (new_args == NULL)
        return (NULL);
    new_args[0] = NULL;
    index = 0;
    while (index < lst_exec->len_expand)
    {
        new_args = ft_add_wildcard(new_args, args[index], ls);
        if (new_args == NULL)
            return (NULL);
        index++;
    }
    return (new_args);
}

char **ft_new_args(t_lst_exec *lst_exec)
{
    char **new_args;
    t_wildcard *ls;

    ls = NULL;
    lst_exec->len_expand = ft_strlen_2d(lst_exec->args);
    new_args = ft_expand_step_1(lst_exec);
    if (new_args == NULL)
        return (NULL);
    if (set_ls(&ls) != SUCCESS)
		return (NULL);//free
    new_args = ft_expand_step_2(lst_exec, new_args, ls);
    if (new_args == NULL)
        return (NULL);
    return (new_args);
}