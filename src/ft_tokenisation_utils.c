/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenisation_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 22:00:40 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/13 22:47:12 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
            if (input[index] == '"')
                double_quote_open = CLOSE;
            index++;
        }
        while (single_quote_open == OPEN && input[index])
        {
            if (input[index] == '\'')
                single_quote_open = CLOSE;
            index++;
        }
    }
    if (double_quote_open == OPEN || single_quote_open == OPEN)
        return (ft_putstr_fd("c'est encore ouvert\n", 2), OPEN);
    return (CLOSE);
}

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