/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bac_a_sable.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 21:21:48 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/13 21:22:14 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int ft_size_new_word(char *input, int index)
{
    int count;
    int double_quote_open;
    int single_quote_open;

    count = 0;
    double_quote_open = CLOSE;
    single_quote_open = CLOSE;
    if (input[index] == '"')
        double_quote_open = OPEN, index++;
    else if (input[index] == '\'')
        single_quote_open = OPEN, index++;
    while ((input[index] != ' ' && double_quote_open == CLOSE && single_quote_open == CLOSE && input[index]) || (double_quote_open == OPEN && input[index]) || (single_quote_open == OPEN && input[index]))
    {
        if (input[index] == '"' && double_quote_open == OPEN)
        {
            double_quote_open = CLOSE;
            break;
        }
        else if (input[index] == '\'' && single_quote_open == OPEN)
        {
            single_quote_open = CLOSE;
            break;
        }
        else
            count++;
        index++;
    }
    return (count);
}

int ft_parse(t_token *token, char *input)
{
    char *str;
    int double_quote_open;
    int single_quote_open;
    int index;
    int new_word;
    int size_new_word;
    int index_new_word;

    if (input[0] == '\0')
        return (free(input), WRONG_INPUT);
    double_quote_open = CLOSE;
    single_quote_open = CLOSE;
    new_word = OPEN;
    index = -1;
    while (input[++index])
    {
        // on gere les nouveaux mots
        if (new_word == OPEN)
        {
            index_new_word = 0;
            size_new_word = ft_size_new_word(input, index);
            if (size_new_word != 0)
            {    
                str = malloc((size_new_word + 1) * sizeof(char));
                if (str == NULL)
                    return (free(input), ERROR_MALLOC); //free les str deja crees pareil pour les tokens deja crees
                new_word = CLOSE;
            }
        }
        // on gere les ouvertures et les fermetures des quotes
        // si on est dans une quote on prend et si on est pas dans une quote on prend tout sauf les espaces
        if (input[index] == '"' && single_quote_open == CLOSE && double_quote_open == CLOSE)
            double_quote_open = OPEN;
        else if (input[index] == '"' && double_quote_open == OPEN)
            double_quote_open = CLOSE;
        else if (input[index] == '\'' && double_quote_open == CLOSE && single_quote_open == CLOSE)
            single_quote_open = OPEN;
        else if (input[index] == '\'' && single_quote_open == OPEN)
            single_quote_open = CLOSE;
        else if ((input[index] != ' ' || double_quote_open == OPEN || single_quote_open == OPEN) && index_new_word < size_new_word)
            str[index_new_word++] = input[index];
        if (new_word == CLOSE && index_new_word >= size_new_word && double_quote_open == CLOSE && single_quote_open == CLOSE)
        {
            str[index_new_word] = '\0';
            ft_lst_add_back(&token, ft_lstnew(str));
            printf("%s\n", str);
            free(str);
            new_word = OPEN;
        }
    }
    if (double_quote_open == OPEN || single_quote_open == OPEN)
    {
        printf("wrong\n");
        return (free(input), WRONG_INPUT);
    }
    return (free(input), GOOD_INPUT);
}