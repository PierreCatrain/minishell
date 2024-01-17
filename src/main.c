/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:52:38 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/17 06:43:51 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int ft_exec(t_tree *tree)
{
    tree = (t_tree *)tree;
    return (SUCCESS);
}

// on verife les conditions pour lancer notre minishell
// on recupere le prompt et on l'affiche
// on recupere l'input de l'utilisateur
// si l'input et valable on l'envoie de maniere structurer a l'exec
// si l'input et pas valable on le signal et on recommence a l'etape 2
int main(int argc, char **argv, char **envp)
{
    t_tree *tree;
    char *prompt;
    char *input;

    tree = NULL;
    argv = (void *)argv;
    if (ft_check_argc_envp(argc, envp) == ERROR_ARGC_ENVP)
        return (ERROR_ARGC_ENVP);
    while (1)
    {
        prompt = ft_get_prompt();
        if (prompt == NULL)
           return (ERROR_PROMPT);
        input = readline(prompt);
        free(prompt);
        if (ft_parse(&tree, input) == GOOD_INPUT)
            ft_exec(tree);
    }
    return (SUCCESS);
}