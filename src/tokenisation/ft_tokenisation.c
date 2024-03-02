/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenisation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 05:06:05 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/02 14:56:32 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int ft_add_token(t_token **token, t_data_parse *data_parse, t_expand *expand)
{
	if (ft_strcmp(data_parse->str, "<<") == 0 && data_parse->single_quote_open == CLOSE && data_parse->double_quote_open == CLOSE)
	{
		if (ft_lst_add_back(token, ft_lstnew(data_parse->str, WORD, HEREDOC, expand)) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	else if (ft_strcmp(data_parse->str, ">>") == 0 && data_parse->single_quote_open == CLOSE && data_parse->double_quote_open == CLOSE)
	{
		if (ft_lst_add_back(token, ft_lstnew(data_parse->str, WORD, APPEND, expand)) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	else if (ft_strcmp(data_parse->str, "<") == 0 && data_parse->single_quote_open == CLOSE && data_parse->double_quote_open == CLOSE)
	{
		if (ft_lst_add_back(token, ft_lstnew(data_parse->str, WORD, INFILE, expand)) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	else if (ft_strcmp(data_parse->str, ">") == 0 && data_parse->single_quote_open == CLOSE && data_parse->double_quote_open == CLOSE)
	{
		if (ft_lst_add_back(token, ft_lstnew(data_parse->str, WORD, OUTFILE, expand)) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	else if (ft_strcmp(data_parse->str, "&&") == 0 && data_parse->single_quote_open == CLOSE && data_parse->double_quote_open == CLOSE)
	{
		if (ft_lst_add_back(token, ft_lstnew(data_parse->str, WORD, AND, expand)) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	else if (ft_strcmp(data_parse->str, "||") == 0 && data_parse->single_quote_open == CLOSE && data_parse->double_quote_open == CLOSE)
	{
		if (ft_lst_add_back(token, ft_lstnew(data_parse->str, WORD, OR, expand)) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	else if (ft_strcmp(data_parse->str, "|") == 0 && data_parse->single_quote_open == CLOSE && data_parse->double_quote_open == CLOSE)
	{
		if (ft_lst_add_back(token, ft_lstnew(data_parse->str, WORD, PIPE, expand)) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	else if (ft_strcmp(data_parse->str, "(") == 0 && data_parse->single_quote_open == CLOSE && data_parse->double_quote_open == CLOSE)
	{
		if (ft_lst_add_back(token, ft_lstnew(data_parse->str, WORD, OPEN_PARENTHESIS, expand)) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	else if (ft_strcmp(data_parse->str, ")") == 0 && data_parse->single_quote_open == CLOSE && data_parse->double_quote_open == CLOSE)
	{
		if (ft_lst_add_back(token, ft_lstnew(data_parse->str, WORD, CLOSE_PARENTHESIS, expand)) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	else if (data_parse->str[0] != '\0')
	{
		if (ft_lst_add_back(token, ft_lstnew(data_parse->str, WORD, TEXT, expand)) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
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
		return (ERROR_MALLOC);
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
			{
				if (ft_lst_add_back(token, ft_lstnew(data_parse->str, WORD, TEXT, expand)) == ERROR_MALLOC)
					return (ERROR_MALLOC);
				data_parse->single_quote_open = CLOSE;
				data_parse->index++; // a voir
				return (SUCCESS);
			}
			data_parse->single_quote_open = CLOSE;
		}
		else if (data_parse->input[data_parse->index] == '"' && data_parse->double_quote_open == OPEN)
		{
			if ((data_parse->input[data_parse->index + 1] == ' ' || data_parse->input[data_parse->index + 1] == '\0') && data_parse->str[0] != '\0')
			{
				if (ft_lst_add_back(token, ft_lstnew(data_parse->str, WORD, TEXT, expand)) == ERROR_MALLOC)
					return (ERROR_MALLOC);
				data_parse->double_quote_open = CLOSE;
				data_parse->index++; // a voir
				return (SUCCESS);
			}
			data_parse->double_quote_open = CLOSE;
		}
		else if (data_parse->input[data_parse->index] == '\'' && data_parse->single_quote_open == CLOSE && data_parse->double_quote_open == CLOSE)
		{
			data_parse->single_quote_open = OPEN;
		}
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

int ft_add_in_opperator(t_data_parse *data_parse)
{
	if (data_parse->input[data_parse->index] == '<' && data_parse->input[data_parse->index + 1] == '<')
	{
		data_parse->str = ft_strjoin_1_malloc(data_parse->str, " << ");
		if (data_parse->str == NULL)
			return (ERROR_MALLOC);
		data_parse->index += 2;
	}
	else if (data_parse->input[data_parse->index] == '>' && data_parse->input[data_parse->index + 1] == '>')
	{
		data_parse->str = ft_strjoin_1_malloc(data_parse->str, " >> ");
		if (data_parse->str == NULL)
			return (ERROR_MALLOC);
		data_parse->index += 2;
	}
	else if (data_parse->input[data_parse->index] == '&' && data_parse->input[data_parse->index + 1] == '&')
	{
		data_parse->str = ft_strjoin_1_malloc(data_parse->str, " && ");
		if (data_parse->str == NULL)
			return (ERROR_MALLOC);
		data_parse->index += 2;
	}
	else if (data_parse->input[data_parse->index] == '|' && data_parse->input[data_parse->index + 1] == '|')
	{
		data_parse->str = ft_strjoin_1_malloc(data_parse->str, " || ");
		if (data_parse->str == NULL)
			return (ERROR_MALLOC);
		data_parse->index += 2;
	}
	else if (data_parse->input[data_parse->index] == '<')
	{
		data_parse->str = ft_strjoin_1_malloc(data_parse->str, " < ");
		if (data_parse->str == NULL)
			return (ERROR_MALLOC);
		data_parse->index++;
	}
	else if (data_parse->input[data_parse->index] == '>')
	{
		data_parse->str = ft_strjoin_1_malloc(data_parse->str, " > ");
		if (data_parse->str == NULL)
			return (ERROR_MALLOC);
		data_parse->index++;
	}
	else if (data_parse->input[data_parse->index] == '(')
	{
		data_parse->str = ft_strjoin_1_malloc(data_parse->str, " ( ");
		if (data_parse->str == NULL)
			return (ERROR_MALLOC);
		data_parse->index++;
	}
	else if (data_parse->input[data_parse->index] == ')')
	{
		data_parse->str = ft_strjoin_1_malloc(data_parse->str, " ) ");
		if (data_parse->str == NULL)
			return (ERROR_MALLOC);
		data_parse->index++;
	}
	else if (data_parse->input[data_parse->index] == '|')
	{
		data_parse->str = ft_strjoin_1_malloc(data_parse->str, " | ");
		if (data_parse->str == NULL)
			return (ERROR_MALLOC);
		data_parse->index++;
	}
	else
	{
		data_parse->str = ft_join_char(data_parse->str, data_parse->input[data_parse->index]);
		if (data_parse->str == NULL)
			return (ERROR_MALLOC);
		data_parse->index++;
	}
	return (SUCCESS);
}

char *ft_isol_operateur(t_data_parse *data_parse)
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

/*
on parcourt tout l'input et on fait des tokens avec
*/
int	ft_tokenisation(t_token **token, t_data_parse *data_parse)
{
	if (ft_is_quote_close(data_parse->input, CLOSE, CLOSE) == OPEN)
		return (free(data_parse->input), WRONG_INPUT);
	data_parse->input = ft_isol_operator(data_parse);
	if (data_parse->input == NULL)
		return (ERROR_MALLOC);
	data_parse->index = 0;
	while (data_parse->input[data_parse->index])
	{
		if (ft_make_token(data_parse, token) != SUCCESS)
			return (ERROR);
	}
	free(data_parse->input);
	if (*token == NULL)
		return (WRONG_INPUT);
	ft_set_all_grammaire(token);
	return (GOOD_INPUT);
}
