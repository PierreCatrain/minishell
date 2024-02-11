/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_wildcard_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 22:02:47 by picatrai          #+#    #+#             */
/*   Updated: 2024/02/02 22:15:02 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_complete_before_after(t_data_parse *data_parse, t_token **token)
{
	while ((*token)->str[++data_parse->index])
	{
		if ((*token)->str[data_parse->index] == '*')
		{
			data_parse->before[data_parse->i] = '\0';
			data_parse->part = 2;
			data_parse->i = 0;
		}
		else
		{
			if (data_parse->part == 1)
				data_parse->before[data_parse->i++] \
				= (*token)->str[data_parse->index];
			else if (data_parse->part == 2)
				data_parse->after[data_parse->i++] \
				= (*token)->str[data_parse->index];
		}
	}
	if (data_parse->part == 2)
		data_parse->after[data_parse->i] = '\0';
}

int	ft_insert_wildcard_before_after(t_wildcard *ls, t_data_parse *data_parse, \
t_token **token, int *find)
{
	while (ls != NULL)
	{
		if (match_with_wildcard(data_parse->before, data_parse->after, ls->str) \
		== SUCCESS)
		{
			if (ft_lst_insert(token, ft_lstnew_no_malloc(ls->str, WORD, TEXT)) \
			== ERROR_MALLOC)
				return (free(data_parse->before), \
				free(data_parse->after), ERROR_MALLOC);
			*find = 1;
		}
		if (ls->prev == NULL)
			break ;
		ls = ls->prev;
	}
	return (SUCCESS);
}

int	ft_wildcard_before_and_after(t_token **token, t_wildcard *ls, int *find)
{
	t_data_parse	data_parse;

	data_parse.index = -1;
	data_parse.i = 0;
	data_parse.part = 1;
	data_parse.before = malloc((ft_strlen_before((*token)->str) + 1) \
	* sizeof(char));
	if (data_parse.before == NULL)
		return (ERROR_MALLOC);
	data_parse.before[0] = '\0';
	data_parse.after = malloc((ft_strlen_after((*token)->str) + 1) \
	* sizeof(char));
	if (data_parse.after == NULL)
		return (free(data_parse.before), ERROR_MALLOC);
	data_parse.after[0] = '\0';
	ft_complete_before_after(&data_parse, token);
	if (ft_insert_wildcard_before_after(ls, &data_parse, token, find) \
	== ERROR_MALLOC)
		return (ERROR_MALLOC);
	return (free(data_parse.before), free(data_parse.after), SUCCESS);
}

int	ft_wildcard_no_before_no_after(t_wildcard **ls, t_token **token, int *find)
{
	while (*ls != NULL)
	{
		if ((*ls)->str[0] != '.')
		{
			if (ft_lst_insert(token, ft_lstnew_no_malloc((*ls)->str, \
			WORD, TEXT)) == ERROR_MALLOC)
				return (ft_print_error_malloc(), \
				ft_free_wildcard(ls), ERROR_MALLOC);
			*find = 1;
		}
		if ((*ls)->prev == NULL)
			break ;
		*ls = (*ls)->prev;
	}
	return (SUCCESS);
}
