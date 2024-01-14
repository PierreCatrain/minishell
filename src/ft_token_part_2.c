/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_part_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 00:58:07 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/14 04:45:40 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int ft_complete_double(char *input, t_data_token *data_token, t_token **token)
{
    if (input[data_token->index] != '"')
        data_token->str[data_token->index_str++] = input[data_token->index++];
    else
    {
        data_token->double_quote_open = CLOSE, data_token->index++;
        data_token->str[data_token->index_str] = '\0';
        if (ft_lst_add_back(token, ft_lstnew(data_token->str, DOUBLE_QUOTES)) == ERROR_MALLOC)
            return (free_tokenisation_2(input, token, data_token), ERROR_MALLOC);
    }
    return (SUCCESS);
}

int ft_complete_single(char *input, t_data_token *data_token, t_token **token)
{
    if (input[data_token->index] != '\'')
        data_token->str[data_token->index_str++] = input[data_token->index++];
    else
    {
        data_token->single_quote_open = CLOSE, data_token->index++;
        data_token->str[data_token->index_str] = '\0';
        if (ft_lst_add_back(token, ft_lstnew(data_token->str, SINGLE_QUOTES)) == ERROR_MALLOC)
            return (free_tokenisation_2(input, token, data_token), ERROR_MALLOC);
    }
    return (SUCCESS);
}

int ft_complete_word(char *input, t_data_token *data_token, t_token **token)
{
    data_token->str[data_token->index_str++] = input[data_token->index++];
    if (input[data_token->index] == ' ' || input[data_token->index] == '\0')
    {
        data_token->new_word = CLOSE;
        data_token->str[data_token->index_str] = '\0';
        if (ft_lst_add_back(token, ft_lstnew(data_token->str, WORD)) == ERROR_MALLOC)
            return (free_tokenisation_2(input, token, data_token), ERROR_MALLOC);
    }
    return (SUCCESS);
}
// on remplie notre token jusqu a ce qu'on detecte la fin de notre token
int ft_token_part_2(char *input, t_data_token *data_token, t_token **token)
{
    while (data_token->double_quote_open == OPEN && input[data_token->index])
    {
        if (ft_complete_double(input, data_token, token) == ERROR_MALLOC)
            return (ERROR_MALLOC);
    }
    while (data_token->single_quote_open == OPEN && input[data_token->index])
    {
        if (ft_complete_single(input, data_token, token) == ERROR_MALLOC)
            return (ERROR_MALLOC);
    }
    while (data_token->new_word == OPEN && input[data_token->index])
    {
        if (ft_complete_word(input, data_token, token) == ERROR_MALLOC)
            return (ERROR_MALLOC);
    }
    return (SUCCESS);
}