/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 01:58:43 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/02 14:37:55 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*ft_lstlast(t_token *token)
{
	if (token == NULL)
		return (NULL);
	while (token->next != NULL)
		token = token->next;
	return (token);
}

t_token	*ft_lstnew(char *str, int quotes, int type, t_expand *expand)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (new == NULL)
		return (free(str), NULL);
	new->str = ft_strdup(str);
	if (new->str == NULL)
		return (free(new), free(str), NULL);
	free(str);
	new->quotes = quotes;
	new->type = type;
	new->expand = expand;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

char	*ft_str_cat_char(char *new_str, char c)
{
	char	*cat;
	int		index;

	cat = malloc((ft_strlen(new_str) + 2) * sizeof(char));
	if (cat == NULL)
		return (free(new_str), NULL);
	index = -1;
	while (new_str[++index])
	{
		cat[index] = new_str[index];
	}
	cat[index++] = c;
	cat[index] = '\0';
	return (free(new_str), cat);
}

char	*ft_replace_exit_status(char *str)
{
	char	*new_str;
	int		index;

	new_str = malloc (sizeof(char));
	if (new_str == NULL)
		return (NULL);
	new_str[0] = '\0';
	index = -1;
	while (str[++index])
	{
		if (str[index] == '$' && str[index + 1] == '?')
		{
			index++;
			new_str = ft_str_cat_long_long(new_str, g_exit_status);
			if (new_str == NULL)
				return (NULL);
		}
		else
		{
			new_str = ft_str_cat_char(new_str, str[index]);
			if (new_str == NULL)
				return (NULL);
		}
	}
	return (new_str);
}

void	ft_free_index_new_args(char **str, int index)
{
	index--;
	while (index >= 0)
		free(str[index]);
	free(str);
}

char	**new_args(char **args)
{
	char	**new_args;
	int		index;

	new_args = malloc ((ft_strlen_2d(args) + 1) * sizeof(char *));
	if (new_args == NULL)
		return (NULL);
	index = -1;
	while (args[++index])
	{
		new_args[index] = ft_replace_exit_status(args[index]);
		if (new_args[index] == NULL)
			return (ft_free_index_new_args(new_args, index), NULL);
	}
	new_args[index] = NULL;
	return (new_args);
}
