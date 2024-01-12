/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_argc_envp.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 21:27:05 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/11 23:50:55 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// verifier au lancemtent de minishell le nombre d'arg, si il y a l'env et si il y a le path dans l'env
int ft_check_argc_envp(int argc, char **envp)
{
    if (argc != 1)
    {
        ft_putstr_fd("Too much arguments\n", 2);
        return (ERROR_ARGC_ENVP);
    }
    if (envp == NULL)
    {
        ft_putstr_fd("No env\n", 2);
        return (ERROR_ARGC_ENVP);
    }
    if (find_path(envp, "PATH=") == NULL)// USER SESSION_MANAGER PWD
    {
        ft_putstr_fd("No PATH in env\n", 2);
        return (ERROR_ARGC_ENVP);
    }
    return (SUCCESS);
}