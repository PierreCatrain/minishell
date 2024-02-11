/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isolate_operateur.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 21:32:59 by picatrai          #+#    #+#             */
/*   Updated: 2024/02/02 03:08:29 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_loop_insert(t_token **token, t_data_parse *data_parse)
{
	if (ft_is_type_2(token, data_parse) == SUCCESS)
	{
		if (ft_insert_operateur_type_2(token, data_parse) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	else if (ft_is_type_1(token, data_parse) == SUCCESS)
	{
		if (ft_insert_operateur_type_1(token, data_parse) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	else
		data_parse->str[data_parse->index_new_str++] \
		= (*token)->str[data_parse->index];
	return (SUCCESS);
}

int	ft_after_loop_insert(t_token **token, t_data_parse *data_parse)
{
	if (ft_is_type_1(token, data_parse) == SUCCESS)
	{
		if (ft_insert_operateur_type_1(token, data_parse) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	else
		data_parse->str[data_parse->index_new_str++] \
		= (*token)->str[data_parse->index];
	return (SUCCESS);
}

int	ft_insert_operateur(t_token **token)
{
	t_data_parse	data_parse;

	if (is_token_valid((*token)->str) == WRONG_INPUT)
		return (WRONG_INPUT);
	data_parse.str = malloc((ft_strlen((*token)->str) + 1) * sizeof(char));
	if (data_parse.str == NULL)
		return (ft_print_error_malloc(), ERROR_MALLOC);
	data_parse.index = ft_strlen((*token)->str);
	data_parse.index_new_str = 0;
	while (--data_parse.index > 0 && (*token)->quotes == WORD)
	{
		if (ft_loop_insert(token, &data_parse) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	if (data_parse.index == 0)
	{
		if (ft_after_loop_insert(token, &data_parse) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	data_parse.str[data_parse.index_new_str] = '\0';
	free((*token)->str);
	(*token)->str = ft_str_rev(data_parse.str);
	if ((*token)->str == NULL)
		return (ft_print_error_malloc(), ERROR_MALLOC);
	return (SUCCESS);
}

void	ft_token_beginning(t_token **token)
{
	while (token != NULL)
	{
		if ((*token)->prev == NULL)
			break ;
		else
			*token = (*token)->prev;
	}
}

int	ft_isolate_operateur(t_token **token)
{
	while (*token != NULL)
	{
		if ((*token)->quotes == WORD && (*token)->type == TEXT)
		{
			if (ft_insert_operateur(token) != SUCCESS)
				return (ERROR);
		}
		if ((*token)->next == NULL)
			break ;
		else
			*token = (*token)->next;
	}
	ft_token_beginning(token);
	while ((*token)->next != NULL)
	{
		if ((*token)->str[0] == '\0')
			ft_lst_del(token);
		else
			*token = (*token)->next;
	}
	if ((*token)->str[0] == '\0')
		ft_lst_del(token);
	ft_token_beginning(token);
	return (SUCCESS);
}
