/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:52:38 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/13 03:04:52 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int ft_exec(t_token token)
{
    token = (t_token)token;
    return (SUCCESS);
}

// on verife les conditions pour lancer notre minishell
// on recupere le prompt et on l'affiche
// on recupere l'input de l'utilisateur
// si l'input et valable on l'envoie de maniere structurer a l'exec
// si l'input et pas valable on le signal et on recommence a l'etape 2
int main(int argc, char **argv, char **envp)
{
    t_token token;
    char *prompt;
    char *input;

    if (ft_check_argc_envp(argc, envp) == ERROR_ARGC_ENVP)
        return (ERROR_ARGC_ENVP);
    argv = (void *)argv;
    while (1)
    {
        prompt = ft_get_prompt();
        if (prompt == NULL)
           return (ERROR_PROMPT);
        input = readline(prompt);
        free(prompt);
        if (ft_parse(&token, input) == GOOD_INPUT)
            ft_exec(token);
    }
    return (SUCCESS);
}

//      if (ft_strncmp(input, "exit", 4) == 0 && ft_strlen(input) == 4)
//          break;