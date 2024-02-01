/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenisation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 05:06:05 by picatrai          #+#    #+#             */
/*   Updated: 2024/02/01 00:08:10 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// on parcourt tout l'input et on fait des tokens avec
// token = mot ou "  " ou '  '
// on remplace les tokens de quotes mot et double quotes par leur variable d'env 
int	ft_tokenisation(t_token **token, t_data_parse *data_parse)
{
	if (ft_is_quote_close(data_parse->input, CLOSE, CLOSE) == OPEN)
		return (free(data_parse->input), WRONG_INPUT);
	data_parse->double_quote_open = CLOSE;
	data_parse->single_quote_open = CLOSE;
	data_parse->new_word = CLOSE;
	data_parse->index = 0;
	while (data_parse->input[data_parse->index])
	{
		data_parse->index_str = 0;
		if (ft_token_part_1(data_parse, token) == ERROR_MALLOC)
			return (ERROR_MALLOC);
		if (ft_token_part_2(data_parse, token) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	free(data_parse->input);
	if (*token == NULL)
		return (WRONG_INPUT);
	if (ft_isolate_operateur(token) != SUCCESS)
		return (ft_free_token(token), ERROR);
	if (ft_replace_env_variable(token) == ERROR_MALLOC)
		return (ft_free_token(token), ERROR_MALLOC);
	if (ft_replace_wildcard(token) != SUCCESS)
		return (ft_free_token(token), ERROR);
	ft_set_all_grammaire(token);
	return (GOOD_INPUT);
}
