/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenisation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 05:06:05 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/17 06:49:59 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// on parcourt tout l'input et on fait des tokens avec
// token = mot ou "  " ou '  '
// on remplace les tokens de quotes mot et double quotes par leur variable d'env 
int ft_tokenisation(t_token **token, char *input)
{
    t_data_token data_token;

    data_token.double_quote_open = CLOSE;
    data_token.single_quote_open = CLOSE;
    data_token.new_word = CLOSE;
    data_token.index = 0;
    while (input[data_token.index])
    {
        data_token.index_str = 0;
        if (ft_token_part_1(input, &data_token, token) == ERROR_MALLOC)
            return (ERROR_MALLOC);
        if (ft_token_part_2(input, &data_token, token) == ERROR_MALLOC)
            return (ERROR_MALLOC);
    }
    free(input);
    if (*token == NULL)
        return (WRONG_INPUT);
    if (ft_isolate_operateur(token) == ERROR_MALLOC)
        return (ERROR_MALLOC);
    if (ft_replace_env_variable(token) == ERROR_MALLOC)
        return (ERROR_MALLOC);
    return (GOOD_INPUT);
}