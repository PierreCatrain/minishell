/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:43:13 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/09 22:18:22 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_isol_word(t_data_parse *data_parse)
{
    char *isol;

    isol = malloc(sizeof(char));
    if (isol == NULL)
        return (NULL);
    isol[0] = '\0';
    while (data_parse->input[data_parse->index] != ' ' && data_parse->input[data_parse->index] != '\0')
    {
        isol = ft_join_char(isol, data_parse->input[data_parse->index]);
        if (isol == NULL)
            return (NULL);
        data_parse->index++;
    }
    return (isol);
}

int	ft_condition_wildcard_2(int *found, char **wildcard, t_wildcard *ls)
{
	*wildcard = ft_strjoin_1_malloc(*wildcard, ls->str);
	if (*wildcard == NULL)
		return (ERROR_MALLOC);
    *wildcard = ft_join_char(*wildcard, ' ');
    if (*wildcard == NULL)
		return (ERROR_MALLOC);
	*found = 1;
	return (SUCCESS);
}

int ft_all_wildcard(t_wildcard *ls, char **wildcard)
{
    while (ls != NULL)
	{
        if (ls->str[0] != '.')
        {
            *wildcard = ft_strjoin_1_malloc(*wildcard, ls->str);
            if (*wildcard == NULL)
                return (ERROR_MALLOC);
            *wildcard = ft_join_char(*wildcard, ' ');
            if (*wildcard == NULL)
                return (ERROR_MALLOC);
        }
        if (ls->next == NULL)
            break ;
        ls = ls->next;
	}
    return (SUCCESS);
}

int	ft_maybe_a_wildcard(t_data_parse *data_parse)
{
    char *isol;
    char **split;
    t_wildcard *ls;
    int found;

    ls = NULL;
    found = 0;
    if (set_ls(&ls) != SUCCESS)
		return (ERROR_MALLOC);
    isol = ft_isol_word(data_parse);
    if (isol == NULL)
        return (ft_free_wildcard(&ls), ERROR_MALLOC);
    data_parse->wildcard = malloc(sizeof(char));
    if (data_parse->wildcard == NULL)
        return (ft_free_wildcard(&ls), free(isol), ERROR_MALLOC);
    data_parse->wildcard[0] = '\0';
    if (ft_occ(isol, '*') == 0)
    {
        free(data_parse->wildcard);
        data_parse->wildcard = isol;
        return (ft_free_wildcard(&ls), SUCCESS);
    }
    if (isol[0] == '*' && ft_strlen(isol) == 1)
    {
        if (ft_all_wildcard(ls, &data_parse->wildcard) != SUCCESS)
            return (ft_free_wildcard(&ls), free(isol), ERROR);
        return (ft_free_wildcard(&ls), free(isol), SUCCESS);
    }
	split = ft_split(isol, '*');
	if (*split == NULL)
		return (ft_free_wildcard(&ls), free(isol), free(data_parse->wildcard), ERROR_MALLOC);
    while (ls != NULL)
	{
		if (ft_check_before(isol, split, ls->str) && ft_check_after(isol, split, \
					ls->str) && ft_check_all(split, ls->str))
		{
			if (ft_condition_wildcard_2(&found, &data_parse->wildcard, ls) == ERROR_MALLOC)
				return (ft_free_wildcard(&ls), free(isol), free_2d(split), ERROR_MALLOC);
		}
        if (ls->next == NULL)
            break ;
		ls = ls->next;
	}
    ft_free_wildcard(&ls);
    free_2d(split);
	if (found == 0)
    {
        free(data_parse->wildcard);
        data_parse->wildcard = isol;
    }
    else
    {
        free(isol);
    }
	return (SUCCESS);
}

char	*ft_wildcard(t_data_parse *data_parse)
{
	data_parse->single_quote_open = CLOSE;
	data_parse->double_quote_open = CLOSE;
	data_parse->str = malloc (sizeof(char));
	if (data_parse->str == NULL)
		return (NULL);
	data_parse->str[0] = '\0';
	data_parse->index = 0;
	while (data_parse->input[data_parse->index])
	{
		ft_change_status_quotes(data_parse);
		if (data_parse->single_quote_open == CLOSE \
				&& data_parse->double_quote_open == CLOSE)
		{
			if (ft_maybe_a_wildcard(data_parse) == ERROR_MALLOC)
				return (NULL);
            data_parse->str = ft_strjoin_1_malloc(data_parse->str, data_parse->wildcard);
            if (data_parse->str == NULL)
                return (free(data_parse->wildcard), NULL);
            free(data_parse->wildcard);
		}
		if (data_parse->input[data_parse->index])
		{
			data_parse->str = ft_join_char(data_parse->str, \
					data_parse->input[data_parse->index++]);
			if (data_parse->str == NULL)
				return (NULL);
		}
	}
	return (free(data_parse->input), data_parse->str);
}
