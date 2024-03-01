/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_env_variable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 23:58:35 by picatrai          #+#    #+#             */
/*   Updated: 2024/02/29 17:57:49 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


char	*ft_str_isolate(char *str, int index_debut, int index_fin)
{
	char	*new_str;
	int	index_new_str;

	index_debut++;
	new_str = malloc((index_fin - index_debut + 1) * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	index_new_str = 0;
	while (index_debut + index_new_str < index_fin)
	{
		new_str[index_new_str] = str[index_debut + index_new_str];
		index_new_str++;
	}
	new_str[index_new_str] = '\0';
	return (new_str);
}



char	*ft_join_char(char *str, char c)
{
	char	*join;
	int			i;

	join = malloc ((ft_strlen(str) + 2) * sizeof(char));
	if (join == NULL)
		return (free(str), NULL);
	i = -1;
	while (str[++i])
		join[i] = str[i];
	join[i++] = c;
	join[i] = '\0';
	return (free(str), join);
}

int ft_lim_isolate(char *str, int index)
{
	index++;
	while (ft_isalphanum(str[index]))
		index++;
	return (index);		
}

char *ft_add_env(char *str, char *new_str, int index)
{
	char *str_isolate;

	str_isolate = ft_str_isolate(str, index, ft_lim_isolate(str, index));
	if (str_isolate == NULL)
		return (free(new_str), NULL);
	new_str = ft_strjoin_one_malloc(new_str, getenv(str_isolate));
	if (new_str == NULL)
		return (free(str_isolate), NULL);
	return (free(str_isolate), new_str);
}

char *ft_replace_env_variable(char *str, t_data_parse *data_parse)
{
	char *new_str;
	int index;

	data_parse->double_quote_open = CLOSE;
	data_parse->single_quote_open = CLOSE;
	data_parse->new_word = CLOSE;
	new_str = malloc(sizeof(char));
	if (new_str == NULL)
		return (NULL);
	new_str[0] = '\0';
	index = -1;
	while (str[++index])
	{
		if (str[index] == '$' && ft_isalphanum(str[index + 1]) && data_parse->single_quote_open == CLOSE)
		{
			new_str = ft_add_env(str, new_str, index);
			if (new_str == NULL)
				return (free(str), NULL);
			index = ft_lim_isolate(str, index) - 1;
		}
		else
		{
			new_str = ft_join_char(new_str, str[index]);
			if (new_str == NULL)
				return (free(str), NULL);
			if (str[index] == '\'' && data_parse->double_quote_open == CLOSE && data_parse->single_quote_open == CLOSE)
				data_parse->single_quote_open = OPEN;
			else if (str[index] == '\'' && data_parse->double_quote_open == CLOSE && data_parse->single_quote_open == OPEN)
				data_parse->single_quote_open = CLOSE;
			else if (str[index] == '"' && data_parse->double_quote_open == CLOSE && data_parse->single_quote_open == CLOSE)
				data_parse->double_quote_open = OPEN;
			else if (str[index] == '"' && data_parse->double_quote_open == OPEN && data_parse->single_quote_open == CLOSE)
				data_parse->double_quote_open = CLOSE;
		}		
	}
	return (free(str), new_str);
}
