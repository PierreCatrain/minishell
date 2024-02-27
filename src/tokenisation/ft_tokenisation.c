/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenisation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 05:06:05 by picatrai          #+#    #+#             */
/*   Updated: 2024/02/27 07:11:56 by picatrai         ###   ########.fr       */
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
	else
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
			if (data_parse->input[data_parse->index + 1] == ' ' || data_parse->input[data_parse->index + 1] == '\0')
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
			if (data_parse->input[data_parse->index + 1] == ' ' || data_parse->input[data_parse->index + 1] == '\0')
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

char *ft_isolate_to_find(t_data_parse *data_parse)
{
	char *str;
	int index;

	str = malloc(sizeof(char));
	if (str == NULL)
		return (NULL);
	str[0] = '\0';
	index = 0;
	while (data_parse->input[data_parse->index + index] && data_parse->input[data_parse->index + index] != ' ' && data_parse->input[data_parse->index + index] != '\'' && data_parse->input[data_parse->index + index] != '"')
	{
		str = ft_join_char(str, data_parse->input[data_parse->index + index]);
		if (str == NULL)
			return (NULL);
		index++;
	}
	return (str);
}

int ft_check_before(char *to_find, char **split, char *str)
{
	if (to_find[0] == '*')
		return (1);
	if (ft_strncmp(split[0], str, ft_strlen(split[0])))
		return (0);
	return (1);
}

int ft_check_after(char *to_find, char **split, char *str)
{
	int index;

	if (to_find[ft_strlen(to_find) - 1] == '*')
		return (1);
	index = ft_strlen(str) - ft_strlen(split[ft_strlen_2d(split) - 1]);
	if (index < 0)
		return (0);
	if (ft_strncmp(split[ft_strlen_2d(split) - 1], &str[index], ft_strlen(split[ft_strlen_2d(split) - 1])))
		return (0);
	return (1);
}

int	ft_strchr_wildcard(char *str, char *find)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i + j] == find[j])
		{
			j++;
			if (j == ft_strlen(find))
				return (i + j);
		}
		i++;
		if (i > ft_strlen(str) - ft_strlen(find))
			return (0);
	}
	return (0);
}

int ft_check_all(char **split, char *str)
{
	int index_split;
	int index_str;
	int tmp;
	int len_str;
	
	len_str = ft_strlen(str);
	index_split = 0;
	index_str = 0;
	while (split[index_split] && index_str < len_str)
	{
		tmp = ft_strchr_wildcard(str, split[index_split++]);
		if (tmp == 0)
			return (0);
		index_str += tmp;
	}
	if (split[index_split] != NULL)
		return (0);
	return (1);
}

int ft_add_in_wildcard(t_data_parse *data_parse)
{
	char *to_find;
	char **split;
	int len;
	t_wildcard	*ls;
	int found;

	found = 0;
	to_find = ft_isolate_to_find(data_parse);
	if (to_find == NULL)
		return (ERROR_MALLOC);
	len = ft_strlen(to_find);
	data_parse->index += len;
	if (len == 0)
	{
		data_parse->str = ft_join_char(data_parse->str, data_parse->input[data_parse->index++]);
		if (data_parse->str == NULL)
			return (ERROR_MALLOC);
	}
	if (ft_occ(to_find, '*') == 0)
	{
		data_parse->str = ft_strjoin(data_parse->str, to_find);
		if (data_parse->str == NULL)
			return (ERROR_MALLOC);
		free(to_find);
		return (SUCCESS);
	}
	split = ft_split(to_find, '*');
	if (split == NULL)
		return (ERROR_MALLOC);
	ls = NULL;
	if (set_ls(&ls) != SUCCESS)
		return (ERROR);
	while (ls->next != NULL)
	{
		if (ft_check_before(to_find, split, ls->str) && ft_check_after(to_find, split, ls->str) && ft_check_all(split, ls->str))
		{
			found = 1;
			data_parse->str = ft_join_char(data_parse->str, ' ');
			if (data_parse->str == NULL)
				return (ERROR_MALLOC);
			data_parse->str = ft_strjoin(data_parse->str, ls->str);
			if (data_parse->str == NULL)
				return (ERROR_MALLOC);
			data_parse->str = ft_join_char(data_parse->str, ' ');
			if (data_parse->str == NULL)
				return (ERROR_MALLOC);
		}
		ls = ls->next;
	}
	if (found == 0)
	{
		data_parse->str = ft_strjoin(data_parse->str, to_find);
		if (data_parse->str == NULL)
			return (ERROR_MALLOC);
	}
	free(to_find);
	return (SUCCESS);
}

char *ft_wildcard(t_data_parse *data_parse)
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
			if (ft_add_in_wildcard(data_parse) == ERROR_MALLOC)
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

// on parcourt tout l'input et on fait des tokens avec
int	ft_tokenisation(t_token **token, t_data_parse *data_parse)
{
	if (ft_is_quote_close(data_parse->input, CLOSE, CLOSE) == OPEN)
		return (free(data_parse->input), WRONG_INPUT);
	// data_parse->input = ft_replace_env_variable(data_parse->input, data_parse);
	// if (data_parse->input == NULL)
	// 	return (ERROR_MALLOC);
	//printf("\t1 %s\n", data_parse->input);
	data_parse->input = ft_isol_operateur(data_parse);
	if (data_parse->input == NULL)
		return (ERROR_MALLOC);
	//printf("\t2 %s\n", data_parse->input);
	data_parse->input = ft_wildcard(data_parse);
	if (data_parse->input == NULL)
		return (ERROR_MALLOC);
	//printf("\t3 %s\n", data_parse->input);
	data_parse->double_quote_open = CLOSE;
	data_parse->single_quote_open = CLOSE;
	data_parse->new_word = CLOSE;
	data_parse->index = 0;
	while (data_parse->input[data_parse->index])
	{
		ft_make_token(data_parse, token);
		// data_parse->index_str = 0;
		// if (ft_token_part_1(data_parse, token) == ERROR_MALLOC)
		// 	return (ERROR_MALLOC);
		// if (ft_token_part_2(data_parse, token) == ERROR_MALLOC)
		// 	return (ERROR_MALLOC);
	}
	//ft_print_token(token);
	free(data_parse->input);
	if (*token == NULL)
		return (WRONG_INPUT);
	// if (ft_isolate_operateur(token) != SUCCESS)
	// 	return (ft_free_token(token), ERROR);
	// if (ft_replace_wildcard(token) != SUCCESS)
	// 	return (ft_free_token(token), ERROR);
	ft_set_all_grammaire(token);
	return (GOOD_INPUT);
}
