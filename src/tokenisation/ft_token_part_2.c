/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_part_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 00:58:07 by picatrai          #+#    #+#             */
/*   Updated: 2024/02/20 00:53:50 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_complete_double(t_data_parse *data_parse, t_token **token)
{
	if (data_parse->input[data_parse->index] != '"')
		data_parse->str[data_parse->index_str++] \
		= data_parse->input[data_parse->index++];
	else
	{
		data_parse->double_quote_open = CLOSE;
		data_parse->index++;
		data_parse->str[data_parse->index_str] = '\0';
		if (ft_lst_add_back(token, ft_lstnew(data_parse->str, \
		DOUBLE_QUOTES, TEXT)) == ERROR_MALLOC)
			return (free_tokenisation_2(token, data_parse), ERROR_MALLOC);
	}
	return (SUCCESS);
}

int	ft_complete_single(t_data_parse *data_parse, t_token **token)
{
	if (data_parse->input[data_parse->index] != '\'')
		data_parse->str[data_parse->index_str++] \
		= data_parse->input[data_parse->index++];
	else
	{
		data_parse->single_quote_open = CLOSE;
		data_parse->index++;
		data_parse->str[data_parse->index_str] = '\0';
		if (ft_lst_add_back(token, ft_lstnew(data_parse->str, \
		SINGLE_QUOTES, TEXT)) == ERROR_MALLOC)
			return (free_tokenisation_2(token, data_parse), ERROR_MALLOC);
	}
	return (SUCCESS);
}

int	ft_complete_word(t_data_parse *data_parse, t_token **token)
{
	data_parse->str[data_parse->index_str++] = \
	data_parse->input[data_parse->index++];
	if (data_parse->input[data_parse->index] == ' ' \
	|| data_parse->input[data_parse->index] == '\0' || data_parse->input[data_parse->index] == '\'' || data_parse->input[data_parse->index] == '"')
	{
		data_parse->new_word = CLOSE;
		data_parse->str[data_parse->index_str++] = '\0';
		if (ft_lst_add_back(token, ft_lstnew(data_parse->str, WORD, TEXT)) \
		== ERROR_MALLOC)
			return (free_tokenisation_2(token, data_parse), ERROR_MALLOC);
	}
	return (SUCCESS);
}

int ft_merge_token(t_token **token)
{
	while ((*token)->next != NULL)
		*token = (*token)->next;
	if ((*token)->prev != NULL)
		*token = (*token)->prev;
	if ((*token)->next->quotes != WORD)
		(*token)->quotes = (*token)->next->quotes;
	(*token)->str = ft_strjoin((*token)->str, (*token)->next->str);
	if ((*token)->str == NULL)
		return (ERROR_MALLOC); // faut free
	free((*token)->next->str);
	free((*token)->next);
	(*token)->next = NULL;
	while ((*token)->prev != NULL)
		*token = (*token)->prev;
	return (SUCCESS);
}

// on remplie notre token jusqu a ce qu'on detecte la fin de notre token
int	ft_token_part_2(t_data_parse *data_parse, t_token **token)
{
	data_parse->merge = 0;
	printf("\tchar : %c\n", data_parse->input[data_parse->index]);
	if (data_parse->index != 0)
	{
		if (data_parse->input[data_parse->index - 1] != ' ')
			data_parse->merge = 1;
	}
	while (data_parse->double_quote_open == OPEN \
	&& data_parse->input[data_parse->index])
	{
		if (ft_complete_double(data_parse, token) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	while (data_parse->single_quote_open == OPEN \
	&& data_parse->input[data_parse->index])
	{
		if (ft_complete_single(data_parse, token) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	while (data_parse->new_word == OPEN && data_parse->input[data_parse->index])
	{
		if (ft_complete_word(data_parse, token) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	if (data_parse->merge == 1)
	{
		if (ft_merge_token(token) != SUCCESS)
			return (ERROR);
	}
	return (SUCCESS);
}
