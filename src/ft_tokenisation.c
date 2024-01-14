/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenisation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 05:06:05 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/14 06:33:29 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int ft_size_malloc_dollars(char *str)
{
    char *variable_env_str;
    char *value_env_str;
    int count;
    int index;
    int count_variable_env_str;
    
    count = 1;
    index = 0;
    while (str[index])
    {
        if (str[index] == '$' && str[index + 1] != '\0')
        {
            index++;
            count_variable_env_str = 0;
            while (str[index + count_variable_env_str] != '$' && str[index + count_variable_env_str])
            {
                
            }
            
        }
        else
        {
            index++;
            count++;
        }
    }
    return (count);
}

int ft_replace_dollars(char *str)
{
    char *new_str;
    int index;

    new_str = malloc (ft_size_malloc_dollars(str) * sizeof(char));
    if (new_str == NULL)
        return (ERROR_MALLOC); // free les tokens
    index = 0;
    while (str[index] && str[index] != '$')
        index++;
    while (str[index] && str[index + 1])
    
}

// on parcourt tout les tokens et on envoie que les mot et double quotes dans la transpho
int     ft_replace_env_variable(t_token **token)
{
    while (*token != NULL)
    {
        if ((*token)->type != SINGLE_QUOTES && ft_occ((*token)->str, '$') != 0)
        {
            (*token)->str = ft_replace_dollars((*token)->str);
            if ((*token)->str == NULL)
                return (ERROR_MALLOC);
        }
        *token = (*token)->next;
    }
}

// on parcourt tout l'input et on fait des tokens avec
// token = mot ou "  " ou '  '
// on remplace les tokens de type mot et double quotes par leur variable d'env 
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
    if (ft_replace_env_variable(token) == ERROR_MALLOC)
        return (ERROR_MALLOC);
    return (GOOD_INPUT);
}