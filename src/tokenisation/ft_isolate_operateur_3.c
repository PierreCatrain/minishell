/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isolate_operateur_3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 02:51:35 by picatrai          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/02/27 08:39:13 by picatrai         ###   ########.fr       */
=======
/*   Updated: 2024/03/01 13:33:26 by picatrai         ###   ########.fr       */
>>>>>>> 4a2c2c7cc4cd1b25115ddc16a6bea9f257eb41a8
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*ft_lstnew_no_malloc(char *str, int quotes, int type, t_expand *expand)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->str = ft_strdup(str);
	if (new->str == NULL)
		return (free(new), NULL);
	new->quotes = quotes;
	new->expand = expand;
	new->type = type;
	new->prev = NULL;
	new->next = NULL;
	return (new);
<<<<<<< HEAD
}

char	*ft_str_rev(char *str)
{
	char	*new_str;
	int		index;
	int		index_new_str;

	new_str = malloc ((ft_strlen(str) + 1) * sizeof(char));
	if (new_str == NULL)
		return (free(str), NULL);
	index = ft_strlen(str);
	index_new_str = 0;
	while (--index >= 0)
		new_str[index_new_str++] = str[index];
	new_str[index_new_str] = '\0';
	return (free(str), new_str);
}

// on s'assure juste que il y ai pas 3 & ou | qui se suivent
int	is_token_valid(char *str)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	while (str[index])
	{
		if (str[index] == '&' || str[index] == '|')
			count++;
		else
			count = 0;
		if (count == 3)
		{
			if (str[index - 2] == '&')
				print_invalid_token("&");
			if (str[index - 2] == '|')
				print_invalid_token("|");
			return (WRONG_INPUT);
		}
		index++;
	}
	return (SUCCESS);
}

int	ft_do_insert(t_token **token, t_data_parse *data_parse, \
char *opperator, int type)
{
	(void)opperator;
	data_parse->str[data_parse->index_new_str] = '\0';
	data_parse->str = ft_str_rev(data_parse->str);
	if (data_parse->str == NULL)
		return (ft_print_error_malloc(), ERROR_MALLOC);
	// if (ft_lst_insert(token, ft_lstnew(data_parse->str, WORD, TEXT)) \
	// == ERROR_MALLOC)
	// 	return (ft_print_error_malloc(), ERROR_MALLOC);
	// if (ft_lst_insert(token, ft_lstnew_no_malloc(opperator, WORD, type)) \
	// == ERROR_MALLOC)
		// return (ft_print_error_malloc(), ERROR_MALLOC);
	data_parse->str = malloc((ft_strlen((*token)->str) + 1) * sizeof(char));
	if (data_parse->str == NULL)
		return (ft_print_error_malloc(), ERROR_MALLOC);
	data_parse->index_new_str = 0;
	if (type == AND || type == OR || type == APPEND || type == HEREDOC)
		data_parse->index--;
	return (SUCCESS);
}
=======
}
>>>>>>> 4a2c2c7cc4cd1b25115ddc16a6bea9f257eb41a8
