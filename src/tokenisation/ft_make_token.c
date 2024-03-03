/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 13:37:36 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/02 06:24:55 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
on ajoute le token avec le bon type
*/
int ft_add_token(t_token **token, t_data_parse *data_parse, t_expand *expand)
{
	char *opp[] = {"<<", ">>", "<", ">", "&&", "||", "|", "(", ")", NULL};
	int type[] = {HEREDOC, APPEND, INFILE, OUTFILE, AND, OR, PIPE, OPEN_PARENTHESIS, CLOSE_PARENTHESIS};
	int index;
	
	index = -1;
	while (++index < 9)
	{
		if (ft_strcmp(data_parse->str, opp[index]) == 0 && data_parse->single_quote_open == CLOSE && data_parse->double_quote_open == CLOSE)
		{
			if (ft_lst_add_back(token, ft_lstnew(data_parse->str, WORD, type[index], expand)) == ERROR_MALLOC)
				return (ERROR_MALLOC);
			return (SUCCESS);
		}
	}
	if (data_parse->str[0] != '\0')
	{
		if (ft_lst_add_back(token, ft_lstnew(data_parse->str, WORD, TEXT, expand)) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	return (SUCCESS);
}

int ft_add_and_return(t_data_parse *data_parse, t_token **token, t_expand *expand)
{
    if (ft_lst_add_back(token, ft_lstnew(data_parse->str, WORD, TEXT, expand)) == ERROR_MALLOC)
		return (ERROR_MALLOC);
	data_parse->double_quote_open = CLOSE;
	data_parse->index++;
	return (SUCCESS);
}

int ft_make_token(t_data_parse *data_parse, t_token **token)
{
	t_expand *expand;

	expand = NULL;
	data_parse->str = malloc(sizeof(char));
	if (data_parse->str == NULL)
		return (ERROR_MALLOC);
	data_parse->str[0] = '\0';
	data_parse->single_quote_open = CLOSE;
	data_parse->double_quote_open = CLOSE;
	while (data_parse->input[data_parse->index] && (data_parse->input[data_parse->index] == ' '))
		data_parse->index++;
	if (data_parse->input[data_parse->index] == '\0')
		return (free(data_parse->str), SUCCESS);
	while (data_parse->input[data_parse->index] && (data_parse->input[data_parse->index] != ' ' || data_parse->single_quote_open == OPEN || data_parse->double_quote_open == OPEN))
	{
		if (data_parse->input[data_parse->index] == '$')
		{
			if (ft_make_lst_expand(&expand, data_parse) == ERROR_MALLOC)
				return (ERROR_MALLOC);
		}
		if (data_parse->input[data_parse->index] == '\'' && data_parse->single_quote_open == OPEN)
		{
			if ((data_parse->input[data_parse->index + 1] == ' ' || data_parse->input[data_parse->index + 1] == '\0') && data_parse->str[0] != '\0')
                return (ft_add_and_return(data_parse, token, expand));
			data_parse->single_quote_open = CLOSE;
		}
		else if (data_parse->input[data_parse->index] == '"' && data_parse->double_quote_open == OPEN)
		{
			if ((data_parse->input[data_parse->index + 1] == ' ' || data_parse->input[data_parse->index + 1] == '\0') && data_parse->str[0] != '\0')
			    return (ft_add_and_return(data_parse, token, expand));
			data_parse->double_quote_open = CLOSE;
		}
		else if (data_parse->input[data_parse->index] == '\'' && data_parse->single_quote_open == CLOSE && data_parse->double_quote_open == CLOSE)
			data_parse->single_quote_open = OPEN;
		else if (data_parse->input[data_parse->index] == '"' && data_parse->single_quote_open == CLOSE && data_parse->double_quote_open == CLOSE)
			data_parse->double_quote_open = OPEN;
		else
		{
			data_parse->str = ft_join_char(data_parse->str, data_parse->input[data_parse->index]);
			if (data_parse->str == NULL)
				return (ERROR_MALLOC);
		}
		data_parse->index++;
	}
	if (ft_add_token(token, data_parse, expand) == ERROR_MALLOC)
		return (ERROR_MALLOC);
	return (SUCCESS);
}