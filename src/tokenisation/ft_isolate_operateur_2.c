/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isolate_operateur_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 02:48:17 by picatrai          #+#    #+#             */
/*   Updated: 2024/02/02 03:10:02 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_is_type_2(t_token **token, t_data_parse *data_parse)
{
	if ((*token)->str[data_parse->index - 1] == '<' \
	&& (*token)->str[data_parse->index] == '<')
		return (SUCCESS);
	else if ((*token)->str[data_parse->index - 1] == '>' \
	&& (*token)->str[data_parse->index] == '>')
		return (SUCCESS);
	else if ((*token)->str[data_parse->index - 1] == '&' \
	&& (*token)->str[data_parse->index] == '&')
		return (SUCCESS);
	else if ((*token)->str[data_parse->index - 1] == '|' \
	&& (*token)->str[data_parse->index] == '|')
		return (SUCCESS);
	return (ERROR);
}

int	ft_insert_operateur_type_2(t_token **token, t_data_parse *data_parse)
{
	if ((*token)->str[data_parse->index - 1] == '<' \
	&& (*token)->str[data_parse->index] == '<')
	{
		if (ft_do_insert(token, data_parse, "<<", HEREDOC) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	else if ((*token)->str[data_parse->index - 1] == '>' \
	&& (*token)->str[data_parse->index] == '>')
	{
		if (ft_do_insert(token, data_parse, ">>", APPEND) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	else if ((*token)->str[data_parse->index - 1] == '&' \
	&& (*token)->str[data_parse->index] == '&')
	{
		if (ft_do_insert(token, data_parse, "&&", AND) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	else if ((*token)->str[data_parse->index - 1] == '|' \
	&& (*token)->str[data_parse->index] == '|')
	{
		if (ft_do_insert(token, data_parse, "||", OR) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	return (SUCCESS);
}

int	ft_is_type_1(t_token **token, t_data_parse *data_parse)
{
	if ((*token)->str[data_parse->index] == '(')
		return (SUCCESS);
	else if ((*token)->str[data_parse->index] == ')')
		return (SUCCESS);
	else if ((*token)->str[data_parse->index] == '<')
		return (SUCCESS);
	else if ((*token)->str[data_parse->index] == '>')
		return (SUCCESS);
	else if ((*token)->str[data_parse->index] == '|')
		return (SUCCESS);
	return (ERROR);
}

int	ft_insert_operateur_type_1_suite(t_token **token, t_data_parse *data_parse)
{
	if ((*token)->str[data_parse->index] == '<')
	{
		if (ft_do_insert(token, data_parse, "<", INFILE) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	else if ((*token)->str[data_parse->index] == '>')
	{
		if (ft_do_insert(token, data_parse, ">", OUTFILE) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	else if ((*token)->str[data_parse->index] == '|')
	{
		if (ft_do_insert(token, data_parse, "|", PIPE) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	return (SUCCESS);
}

int	ft_insert_operateur_type_1(t_token **token, t_data_parse *data_parse)
{
	if ((*token)->str[data_parse->index] == '(')
	{
		if (ft_do_insert(token, data_parse, "(", OPEN_PARENTHESIS) \
				== ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	else if ((*token)->str[data_parse->index] == ')')
	{
		if (ft_do_insert(token, data_parse, ")", CLOSE_PARENTHESIS) \
				== ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	else
	{
		if (ft_insert_operateur_type_1_suite(token, data_parse) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	return (SUCCESS);
}
