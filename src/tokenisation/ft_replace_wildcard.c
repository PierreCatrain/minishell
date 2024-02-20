/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_wildcard.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:41:55 by picatrai          #+#    #+#             */
/*   Updated: 2024/02/19 23:03:01 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_insert_wildcard(t_token **token)
{
	t_wildcard	*ls;
	int			find;

	find = 0;
	ls = NULL;
	if (set_ls(&ls) != SUCCESS)
		return (ERROR);
	if (ls == NULL)
		return (SUCCESS);
	while (ls->next != NULL)
		ls = ls->next;
	if (ft_strlen((*token)->str) == 1)
	{
		if (ft_wildcard_no_before_no_after(&ls, token, &find) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	else
	{
		if (ft_wildcard_before_and_after(token, ls, &find) == ERROR_MALLOC)
			return (ft_print_error_malloc(), \
			ft_free_wildcard(&ls), ERROR_MALLOC);
	}
	if (find == 1)
		ft_lst_del(token);
	return (ft_free_wildcard(&ls), SUCCESS);
}

int	ft_is_there_wildcard(char *str)
{
	int	index;
	int	count;

	index = -1;
	count = 0;
	while (str[++index])
	{
		if (str[index] == '*')
			count++;
	}
	if (count == 1)
		return (SUCCESS);
	return (1);
}

int	ft_replace_wildcard(t_token **token)
{
	while (*token != NULL)
	{
		if ((*token)->quotes == WORD && (*token)->type == TEXT \
		&& ft_is_there_wildcard((*token)->str) == SUCCESS)
		{
			if (ft_insert_wildcard(token) != SUCCESS)
				return (ERROR);
		}
		if ((*token)->next == NULL)
			break ;
		else
			*token = (*token)->next;
	}
	while (token != NULL)
	{
		if ((*token)->prev == NULL)
			break ;
		else
			*token = (*token)->prev;
	}
	return (SUCCESS);
}
