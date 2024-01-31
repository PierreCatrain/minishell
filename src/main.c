/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:52:38 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/31 01:20:38 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int ft_exec(t_tree *tree, char **envp)
{
    tree = (t_tree *)tree;
    envp = (char **)envp;
    free_tree(tree);
    return (SUCCESS);
}

// on verife les conditions pour lancer notre minishell
// on recupere le prompt et on l'affiche
// on recupere l'input de l'utilisateur
// si l'input et valable on l'envoie de maniere structurer a l'exec
// si l'input et pas valable on le signal et on recommence a l'etape 2
int main(int argc, char **argv, char **envp)
{
    t_data_parse data_parse;
    t_tree *tree;

    tree = NULL;
    if (ft_check_argc_envp(argc, argv) == ERROR_ARGC_ENVP)
        return (ERROR_ARGC_ENVP);
    if (argc == 3)
    {
        data_parse.input = ft_strdup(argv[2]);
        if (data_parse.input == NULL)
            return (ERROR_MALLOC);
        if (ft_parse(&tree, &data_parse) == GOOD_INPUT)
            ft_exec(tree, envp);
        return (SUCCESS);
    }
    while (1)
    {
        data_parse.prompt = ft_get_prompt();
        if (data_parse.prompt == NULL)
           return (ERROR_PROMPT);
        data_parse.input = readline(data_parse.prompt);
        free(data_parse.prompt);
        tree = NULL;
        if (ft_parse(&tree, &data_parse) == GOOD_INPUT)
            ft_exec(tree, envp);
    }
    return (SUCCESS);
}

/*
cat && test || (cattt && dsdf)
cat || test || (cattt && dsdf)
*/

/*
a faire

leak en cas d'erreurs de malloc ou pipe
leak en cas d'erreurs de grammaire
signaux
$?
*


ameliorer

les erreurs d'invalide tokens
le variable d'env
bollean garif
les prios dans l'abre binaire
*/