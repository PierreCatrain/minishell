/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 00:23:08 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/17 06:51:10 by picatrai         ###   ########.fr       */
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

// on verifie que le dernier token est un mot et pas un opperateur
// que le premier token n'est pas une pipe
// on verifie que les operateur de redirections sont bien suivi par un mot
// que les pipes sont precede d'un mot
int ft_condition_grammaire(t_token *token)
{
    if (ft_lstlast(token)->type != TEXT)
        return (WRONG_INPUT);
    if (token->type == PIPE)
        return (WRONG_INPUT);
    while (token->next != NULL)
    {
        if ((token->type == INFILE || token->type == OUTFILE || token->type == HEREDOC || token->type == APPEND) && token->next->type != TEXT)
            return (WRONG_INPUT);
        if (token->type != TEXT && token->next->type == PIPE)
            return (WRONG_INPUT);
        token = token->next;
    }
    return (GOOD_INPUT);
}

// je verifie que rien ne m'empeche de faire mes tokens (input vide ou quotes par ferme)
// on fait les tokens et si erreur de malloc alors on cancel l'input en cours et on remet le prompt
// on traite les tokens.
int ft_parse(t_tree **tree, char *input)
{
    t_token *token;
    
    token = NULL;
    if (input[0] == '\0' || ft_is_quote_close(input, CLOSE, CLOSE) == OPEN)
        return (free(input), WRONG_INPUT);
    if (ft_tokenisation(&token, input) == ERROR_MALLOC)
        return (ft_putstr_fd("malloc failed\n", 2), ERROR_MALLOC);
    if (ft_condition_grammaire(token) == WRONG_INPUT)
        return (ft_free_token(&token), WRONG_INPUT);
    ft_print_token(&token);
    if (ft_create_tree(tree, token) != SUCCESS)
        return (ft_free_token(&token), ERROR_MALLOC);
    printf("sorti\n");
    ft_free_token(&token);
    return (GOOD_INPUT);
}