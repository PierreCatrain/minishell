/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 00:23:08 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/13 23:02:22 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int ft_parse(t_token *token, char *input)
{
    int index;
    int index_str;
    char *str;
    int double_quote_open;
    int single_quote_open;
    int new_word;
    int size_malloc;

    double_quote_open = CLOSE;
    single_quote_open = CLOSE;
    new_word = CLOSE;
    index = 0;

    if (input[0] == '\0' || ft_is_quote_close(input, CLOSE, CLOSE) == OPEN)
        return (free(input), WRONG_INPUT);
    while (input[index])
    {
        index_str = 0;
        if (input[index] == '"')
        {
            double_quote_open = OPEN, index++;
            size_malloc = ft_size_malloc(input, index, '"');
            if (size_malloc >= 1)
            {
                str = malloc (size_malloc * sizeof(char));
                if (str == NULL)
                    return (ERROR_MALLOC);// free les tokens deja alloue   
            }
            else
                double_quote_open = CLOSE, index++;
        }
        else if (input[index] == '\'')
        {
            single_quote_open = OPEN, index++;
            size_malloc = ft_size_malloc(input, index, '\'');
            if (size_malloc >= 1)
            {
                str = malloc (size_malloc * sizeof(char));
                if (str == NULL)
                    return (ERROR_MALLOC);// free les tokens deja alloue   
            }
            else
                single_quote_open = CLOSE, index++;
        }
        else if (input[index] != ' ')
        {
            new_word = OPEN;
            str = malloc (ft_size_malloc(input, index, ' ') * sizeof(char));
            if (str == NULL)
                return (ERROR_MALLOC);// free les tokens deja alloue
        }
        else
            index++;
        while (double_quote_open == OPEN && input[index])
        {
            if (input[index] != '"')
                str[index_str++] = input[index++];
            else
            {
                double_quote_open = CLOSE, index++;
                str[index_str] = '\0';
                ft_lst_add_back(&token, ft_lstnew(str));
                free(str);
            }
        }
        while (single_quote_open == OPEN && input[index])
        {
            if (input[index] != '\'')
                str[index_str++] = input[index++];
            else
            {
                single_quote_open = CLOSE, index++;
                str[index_str] = '\0';
                ft_lst_add_back(&token, ft_lstnew(str));
                free(str);
            }
        }
        while (new_word == OPEN && input[index])
        {
            str[index_str++] = input[index++];
            if (input[index] == ' ' || input[index] == '\0')
            {
                new_word = CLOSE;
                str[index_str] = '\0';
                ft_lst_add_back(&token, ft_lstnew(str));
                free(str);
            }
        }
    }
    return (GOOD_INPUT);
}

//test "" test "le grand test" "" 'bn'