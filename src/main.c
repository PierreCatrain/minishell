/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:52:38 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/11 22:25:40 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int main(int argc, char **argv, char **envp)
{
    if (ft_check_argc_envp(argc, envp) == ERROR_ARGC_ENVP)
        return (ERROR_ARGC_ENVP);
    argv = NULL;
    ft_put_prompt(envp);
    return (0);
}