/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_argc_envp.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 21:27:05 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/22 13:59:03 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//on verifie si le path contient /usr/bin
// soit just /usr/bin et \0
// soit il demarre par /usr/bin:
// soit il fini par :/usr/bin
// soit il contient :/usr/bin: au debut, millieu ou fin
// pareil pour /usr/bin/
int ft_check_minimum_path(void)
{
    char *path;
    int correct;

    correct = 0;
    path = getenv("PATH");
    if (ft_strncmp(path, "/usr/bin:", 9) == 0)
        correct = 1;
    else if (ft_strncmp(path, "/usr/bin", 8) == 0 && ft_strlen(path) == 8)
        correct = 1;
    else if (ft_strchr(path, ":/usr/bin:") == 1)
        correct = 1;
    else if (ft_strncmp(&path[ft_strlen(path) - ft_strlen(":/usr/bin")], ":/usr/bin", ft_strlen(":/usr/bin")) == 0)
        correct = 1;
    else if (ft_strncmp(path, "/usr/bin/:", 10) == 0)
        correct = 1;
    else if (ft_strncmp(path, "/usr/bin/", 9) == 0 && ft_strlen(path) == 8)
        correct = 1;
    else if (ft_strchr(path, ":/usr/bin/:") == 1)
        correct = 1;
    else if (ft_strncmp(&path[ft_strlen(path) - ft_strlen(":/usr/bin/")], ":/usr/bin/", ft_strlen(":/usr/bin/")) == 0)
        correct = 1;
    if (correct == 0)
        return (ERROR_ARGC_ENVP);
    return (SUCCESS);
}

//verifier au lancemtent de minishell 
//le nombre d'arg 
//si il y a l'env
//si il y a le path dans l'env
//si le path contient /usr/bin
int ft_check_argc_envp(int argc, char **argv)// il y a plein d'autres cas a gerer on verra au moment des tests
{
    if (argc != 1 && argc != 3)
    {
        ft_putstr_fd("USAGE : ./minishell\n", 2);
        ft_putstr_fd("or\n", 2);
        ft_putstr_fd("USAGE : ./minishell -c \"input\"\n", 2);
        return (ERROR_ARGC_ENVP);
    }
    else if (argc == 3 && ft_strcmp(argv[1], "-c") != 0)
    {
        ft_putstr_fd("USAGE : ./minishell\n", 2);
        ft_putstr_fd("or\n", 2);
        ft_putstr_fd("USAGE : ./minishell -c \"input\"\n", 2);
        return (ERROR_ARGC_ENVP);
    }
    return (SUCCESS);
}