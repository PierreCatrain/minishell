/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_part_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 00:53:58 by picatrai          #+#    #+#             */
/*   Updated: 2024/02/20 00:31:15 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_size_malloc(char *input, int index, char c)
{
	int	count;

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

int	ft_open_double(t_data_parse *data_parse, t_token **token)
{
	int	size_malloc;

	data_parse->double_quote_open = OPEN;
	data_parse->index++;
	size_malloc = ft_size_malloc(data_parse->input, data_parse->index, '"');
	if (size_malloc >= 1)
	{
		data_parse->str = malloc ((size_malloc + 1) * sizeof(char));
		if (data_parse->str == NULL)
			return (free_tokenisation_1(data_parse->input, token), \
			ERROR_MALLOC);
	}
	else
	{
		data_parse->double_quote_open = CLOSE;
		data_parse->index++;
	}
	return (SUCCESS);
}

int	ft_open_single(t_data_parse *data_parse, t_token **token)
{
	int	size_malloc;

	data_parse->single_quote_open = OPEN;
	data_parse->index++;
	size_malloc = ft_size_malloc(data_parse->input, data_parse->index, '\'');
	if (size_malloc >= 1)
	{
		data_parse->str = malloc ((size_malloc + 1) * sizeof(char));
		if (data_parse->str == NULL)
			return (free_tokenisation_1(data_parse->input, token), \
			ERROR_MALLOC);
	}
	else
	{
		data_parse->single_quote_open = CLOSE;
		data_parse->index++;
	}
	return (SUCCESS);
}

int	ft_open_word(t_data_parse *data_parse, t_token **token)
{
	int size;

	size = (ft_size_malloc(data_parse->input, data_parse->index, ' ') + 1);
	if ((size > ft_size_malloc(data_parse->input, data_parse->index, '\'') + 1))
		size = ft_size_malloc(data_parse->input, data_parse->index, '\'') + 1;
	if ((size > ft_size_malloc(data_parse->input, data_parse->index, '"') + 1))
		size = ft_size_malloc(data_parse->input, data_parse->index, '"') + 1;
	data_parse->new_word = OPEN;
	data_parse->str = malloc (size * sizeof(char));
	if (data_parse->str == NULL)
		return (free_tokenisation_1(data_parse->input, token), ERROR_MALLOC);
	return (SUCCESS);
}

// on detecte l'arriver dans un nouveau token et on malloc l'espace pour
int	ft_token_part_1(t_data_parse *data_parse, t_token **token)
{
	if (data_parse->input[data_parse->index] == '"')
	{
		if (ft_open_double(data_parse, token) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	else if (data_parse->input[data_parse->index] == '\'')
	{
		if (ft_open_single(data_parse, token) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	else if (data_parse->input[data_parse->index] != ' ')
	{
		if (ft_open_word(data_parse, token) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	else
	{
		data_parse->index++;
		if (ft_token_part_1(data_parse, token) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	return (SUCCESS);
}
