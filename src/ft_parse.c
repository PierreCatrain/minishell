/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 00:23:08 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/22 18:49:11 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// on s'assure que les quotes ouvertes sont bien ferme sinon l'input n'est pas traitable
int ft_is_quote_close(char *input, int double_quote_open, int single_quote_open)
{
    int index;

    index = 0;
    while (input[index])
    {
        if (input[index] == '"')
            double_quote_open = OPEN;
        else if (input[index] == '\'')
            single_quote_open = OPEN;
        index++;
        while (double_quote_open == OPEN && input[index])
        {
            if (input[index++] == '"')
                double_quote_open = CLOSE;
        }
        while (single_quote_open == OPEN && input[index])
        {
            if (input[index++] == '\'')
                single_quote_open = CLOSE;
        }
    }
    if (double_quote_open == OPEN || single_quote_open == OPEN)
        return (ft_putstr_fd("unclosed quotes\n", 2), OPEN);
    return (CLOSE);
}

// je verifie que rien ne m'empeche de faire mes tokens (input vide ou quotes par ferme)
// on fait les tokens et si erreur de malloc alors on cancel l'input en cours et on remet le prompt
// on traite les tokens
int ft_parse(t_tree **tree, t_data_parse *data_parse)
{
    t_token *token;

    token = NULL;
    if (data_parse->input[0] == '\0' || ft_is_quote_close(data_parse->input, CLOSE, CLOSE) == OPEN)
        return (free(data_parse->input), WRONG_INPUT);
    if (ft_tokenisation(&token, data_parse) == ERROR_MALLOC)
        return (ft_putstr_fd("malloc failed\n", 2), ERROR_MALLOC);
    if (ft_condition_grammaire(token) == WRONG_INPUT)
        return (ft_free_token(&token), WRONG_INPUT);
    //ft_print_token(&token);
    if (ft_create_tree(tree, token) != SUCCESS)
        return (ft_free_token(&token), ERROR_MALLOC);
    //ft_free_token(&token);
    ft_print_tree(*tree);
    return (GOOD_INPUT);
}