/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_part_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 00:53:58 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/14 04:13:24 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int ft_size_malloc(char *input, int index, char c)
{
    int count;

    count = 0;
    while (input[index] != c && input[index])
    {
        index++;
        count++;
    }
    if (input[index] != '\0' && input[index] != c)
        count++;
    return (count);
}

int ft_open_double(char *input, t_data_token *data_token, t_token **token)
{
    int size_malloc;
    
    data_token->double_quote_open = OPEN, data_token->index++;
    size_malloc = ft_size_malloc(input, data_token->index, '"');
    if (size_malloc >= 1)
    {
        data_token->str = malloc (size_malloc * sizeof(char));
        if (data_token->str == NULL)
            return (free_tokenisation_1(input, token), ERROR_MALLOC); 
    }
    else
        data_token->double_quote_open = CLOSE, data_token->index++;
    return (SUCCESS);
}

int ft_open_single(char *input, t_data_token *data_token, t_token **token)
{
    int size_malloc;
    
    data_token->single_quote_open = OPEN, data_token->index++;
    size_malloc = ft_size_malloc(input, data_token->index, '\'');
    if (size_malloc >= 1)
    {
        data_token->str = malloc (size_malloc * sizeof(char));
        if (data_token->str == NULL)
            return (free_tokenisation_1(input, token), ERROR_MALLOC);
    }
    else
        data_token->single_quote_open = CLOSE, data_token->index++;
    return (SUCCESS);
}

int ft_open_word(char *input, t_data_token *data_token, t_token **token)
{
    data_token->new_word = OPEN;
    data_token->str = malloc (ft_size_malloc(input, data_token->index, ' ') * sizeof(char));
    if (data_token->str == NULL)
        return (free_tokenisation_1(input, token), ERROR_MALLOC);
    return (SUCCESS);
}

// on detecte l'arriver dans un nouveau token et on malloc l'espace pour
int ft_token_part_1(char *input, t_data_token *data_token, t_token **token)
{
    if (input[data_token->index] == '"')
    {
        if (ft_open_double(input, data_token, token) == ERROR_MALLOC)
            return (ERROR_MALLOC);
    }
    else if (input[data_token->index] == '\'')
    {
        if (ft_open_single(input, data_token, token) == ERROR_MALLOC)
            return (ERROR_MALLOC);
    }
    else if (input[data_token->index] != ' ')
    {
        if (ft_open_word(input, data_token, token) == ERROR_MALLOC)
            return (ERROR_MALLOC);
    }
    else
        data_token->index++;
    return (SUCCESS);
}