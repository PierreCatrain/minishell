/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_wildcard_3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 22:06:56 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/01 11:46:17 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_free_wildcard(t_wildcard **ls)
{
	t_wildcard	*tmp;

	while ((*ls)->prev != NULL)
		*ls = (*ls)->prev;
	while (*ls != NULL)
	{
		tmp = *ls;
		*ls = (*ls)->next;
		free(tmp->str);
		free(tmp);
	}
}

int	ft_strlen_before(char *str)
{
	int	index;

	index = 0;
	while (str[index] && str[index] != '*')
		index++;
	return (index);
}

int	ft_strlen_after(char *str)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	while (str[index] && str[index] != '*')
		index++;
	if (str[index] == '*')
		index++;
	while (str[index++])
		count++;
	return (count);
}

char	*ft_only_end_str(char *str, int size)
{
	int	index;

	index = 0;
	while (str[index])
		index++;
	if (index < size)
		return (NULL);
	return (&str[index - size]);
}

int	match_with_wildcard(char *before, char *after, char *str)
{
	int	good;

	if ((ft_strlen(before) + ft_strlen(after)) > ft_strlen(str))
		return (ERROR);
	good = 0;
	if ((before == NULL && str[0] != '.') || ft_strncmp(before, \
	str, ft_strlen(before)) == 0)
		good++;
	if (after == NULL || ft_strncmp(after, ft_only_end_str(str, \
	ft_strlen(after)), ft_strlen(after)) == 0)
		good++;
	if (good != 2)
		return (ERROR);
	return (SUCCESS);
}
