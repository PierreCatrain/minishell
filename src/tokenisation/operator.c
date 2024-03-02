/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 13:29:01 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/02 06:35:27 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int ft_add_in_opperator(t_data_parse *data_parse)
{
	char condition_1[] = {'<', '>', '&', '|'};
	char *res_1[] = {" << ", " >> ", " && ", " || "};
	char condition_2[] = {'<', '>', '(', ')', '|'};
	char *res_2[] = {" < ", " > ", " ( ", " | "};
	int index;

	index = -1;
	while (++index < 4)
	{
		if (data_parse->input[data_parse->index] == condition_1[index] && data_parse->input[data_parse->index + 1] == condition_1[index])
		{
			data_parse->str = ft_strjoin_1_malloc(data_parse->str, res_1[index]);
			if (data_parse->str == NULL)
				return (ERROR_MALLOC);
			data_parse->index += 2;
			return (SUCCESS);
		}
	}
	index = -1;
	while (++index < 4)
	{
		if (data_parse->input[data_parse->index] == condition_2[index])
		{
			data_parse->str = ft_strjoin_1_malloc(data_parse->str, res_2[index]);
			if (data_parse->str == NULL)
				return (ERROR_MALLOC);
			data_parse->index++;
			return (SUCCESS);
		}
	}
	data_parse->str = ft_join_char(data_parse->str, data_parse->input[data_parse->index]);
	if (data_parse->str == NULL)
		return (ERROR_MALLOC);
	data_parse->index++;
	return (SUCCESS);
}

char *ft_isol_operator(t_data_parse *data_parse)
{
	int single_quotes;
	int double_quotes;
	
	single_quotes = CLOSE;
	double_quotes = CLOSE;
	data_parse->str = malloc (sizeof(char));
	if (data_parse->str == NULL)
		return (NULL);
	data_parse->str[0] = '\0';
	data_parse->index = 0;
	while (data_parse->input[data_parse->index])
	{
		if (data_parse->input[data_parse->index] == '\'' && single_quotes == OPEN)
			single_quotes = CLOSE;
		else if (data_parse->input[data_parse->index] == '"' && double_quotes == OPEN)
			double_quotes = CLOSE;
		else if (data_parse->input[data_parse->index] == '\'' && single_quotes == CLOSE && double_quotes == CLOSE)
			single_quotes = OPEN;
		else if (data_parse->input[data_parse->index] == '"' && single_quotes == CLOSE && double_quotes == CLOSE)
			double_quotes = OPEN;
		if (single_quotes == CLOSE && double_quotes == CLOSE)
		{
			if (ft_add_in_opperator(data_parse) == ERROR_MALLOC)
				return (NULL);
		}
		else
		{
			data_parse->str = ft_join_char(data_parse->str, data_parse->input[data_parse->index]);
			if (data_parse->str == NULL)
				return (NULL);
			data_parse->index++;
		}
	}
	free(data_parse->input);
	return (data_parse->str);
}
