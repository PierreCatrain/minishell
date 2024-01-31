/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_num_builtins.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:48:13 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/31 00:57:16 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int is_builtin_echo(t_lst_exec *lst_exec)
{
    int len;

    len = ft_strlen_2d(lst_exec->args);
    if (len < 2)
        return (ERROR);
    if (ft_strcmp("echo", lst_exec->args[0]) != 0)
        return (ERROR);
    if (ft_strcmp("-n", lst_exec->args[1]) != 0)
        return (ERROR);
    return (SUCCESS);
}

int is_builtin_cd(t_lst_exec *lst_exec)
{
    int len;

    len = ft_strlen_2d(lst_exec->args);
    if (len < 2)
        return (ERROR);
    if (ft_strcmp("cd", lst_exec->args[0]) != 0)
        return (ERROR);
    return (SUCCESS);
}

int is_builtin_pwd(t_lst_exec *lst_exec)
{
    int len;

    len = ft_strlen_2d(lst_exec->args);
    if (len != 1)
        return (ERROR);
    if (ft_strcmp("pwd", lst_exec->args[0]) != 0)
        return (ERROR);
    return (SUCCESS);
}

int is_builtin_export(t_lst_exec *lst_exec)
{
    if (ft_strcmp("export", lst_exec->args[0]) != 0)
        return (ERROR);
    return (SUCCESS);
}

int is_builtin_unset(t_lst_exec *lst_exec)
{
    if (ft_strcmp("unset", lst_exec->args[0]) != 0)
        return (ERROR);
    return (SUCCESS);
}

int is_builtin_env(t_lst_exec *lst_exec)
{
    int len;

    len = ft_strlen_2d(lst_exec->args);
    if (len != 1)
        return (ERROR);
    if (ft_strcmp("env", lst_exec->args[0]) != 0)
        return (ERROR);
    return (SUCCESS);
}

int is_builtin_exit(t_lst_exec *lst_exec)
{
    if (ft_strcmp("exit", lst_exec->args[0]) != 0)
        return (ERROR);
    return (SUCCESS);
}

void ft_add_num_builtins(t_lst_exec **lst_exec)
{
    while (*lst_exec != NULL)
    {
        if (is_builtin_echo(*lst_exec) == SUCCESS)
            (*lst_exec)->builtin = 1;
        else if (is_builtin_cd(*lst_exec) == SUCCESS)
            (*lst_exec)->builtin = 2;
        else if (is_builtin_pwd(*lst_exec) == SUCCESS)
            (*lst_exec)->builtin = 3;
        else if (is_builtin_export(*lst_exec) == SUCCESS)
            (*lst_exec)->builtin = 4;
        else if (is_builtin_unset(*lst_exec) == SUCCESS)
            (*lst_exec)->builtin = 5;
        else if (is_builtin_env(*lst_exec) == SUCCESS)
            (*lst_exec)->builtin = 6;
        else if (is_builtin_exit(*lst_exec) == SUCCESS)
            (*lst_exec)->builtin = 7;
        else
            (*lst_exec)->builtin = 0;
        if ((*lst_exec)->next == NULL)
            break;
        *lst_exec = (*lst_exec)->next;
    }
    while ((*lst_exec)->prev != NULL)
    {
        *lst_exec = (*lst_exec)->prev;
    }
}
