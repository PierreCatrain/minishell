/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_argc_envp.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 21:27:05 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/14 05:34:26 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//on verifie si le path contient /usr/bin
// soit just /usr/bin et \0
// soit il demarre par /usr/bin:
// soit il fini par :/usr/bin
// soit il contient :/usr/bin: au debut, millieu ou fin
int ft_check_minimum_path(void)
{
    char *path;

    path = getenv("PATH");
    if (ft_strncmp(path, "/usr/bin:", 9) == 1 \
    && (ft_strncmp(path, "/usr/bin", 8) == 0 && ft_strlen(path) != 8) \
    && ft_strchr(path, ":/usr/bin:") == 0 \
    && ft_strncmp(&path[ft_strlen(path) - ft_strlen(":/usr/bin")], ":/usr/bin", ft_strlen(":/usr/bin")) == 1) // il faut autoriser /usr/bin/
        return (ERROR_ARGC_ENVP);
    return (SUCCESS);
}

//verifier au lancemtent de minishell 
//le nombre d'arg 
//si il y a l'env
//si il y a le path dans l'env
//si le path contient /usr/bin
int ft_check_argc_envp(int argc, char **envp)
{
    if (argc != 1)
    {
        ft_putstr_fd("Too much arguments\n", 2);
        return (ERROR_ARGC_ENVP);
    }
    else if (envp == NULL)
    {
        ft_putstr_fd("No env\n", 2);
        return (ERROR_ARGC_ENVP);
    }
    else if (getenv("PATH") == NULL)
    {
        ft_putstr_fd("Need PATH", 2);
        return (ERROR_ARGC_ENVP);
    }
    else if (ft_check_minimum_path() == ERROR_ARGC_ENVP)
    {
        ft_putstr_fd("Need correct PATH", 2);
        return (ERROR_ARGC_ENVP);
    }
    return (SUCCESS);
}