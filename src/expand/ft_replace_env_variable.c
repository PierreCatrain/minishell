/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_env_variable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 07:05:34 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/05 10:27:36 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_not_replace(char *str, char **new_str, int index, t_expand **expand)
{
	if (str[index] == '$' && str[index + 1] == '?' && (*expand)->act == KEEP)
	{
		*new_str = ft_join_char(*new_str, str[index]);
		if (*new_str == NULL)
			return (ERROR_MALLOC);
		*expand = (*expand)->next;
	}
	else if (str[index] == '$' && (*expand)->act == KEEP)
	{
		*new_str = ft_join_char(*new_str, str[index]);
		if (new_str == NULL)
			return (ERROR_MALLOC);
		*expand = (*expand)->next;
	}
	else
	{
		*new_str = ft_join_char(*new_str, str[index]);
		if (*new_str == NULL)
			return (ERROR_MALLOC);
	}
	return (SUCCESS);
}

int	rep_status(int *index, char **new_str, int status, t_expand **expand)
{
	(*index)++;
	*new_str = ft_str_cat_long_long(*new_str, status);
	if (new_str == NULL)
		return (ERROR_MALLOC);
	*expand = (*expand)->next;
	return (SUCCESS);
}

int	ft_set_replace_env_variable(char **new_str, int *index)
{
	*index = 0;
	*new_str = malloc(sizeof(char));
	if (*new_str == NULL)
		return (ERROR_MALLOC);
	*new_str[0] = '\0';
	return (SUCCESS);
}

char	*ft_replace_env_variable(char *str, t_expand *expand, \
		char **env, int status)
{
	char	*new_str;
	int		index;

	new_str = NULL;
	if (ft_set_replace_env_variable(&new_str, &index) == ERROR_MALLOC)
		return (NULL);
	while (str[index])
	{
		if (str[index] == '$' && str[index + 1] == '?' && expand->act == CHANGE)
		{
			if (rep_status(&index, &new_str, status, &expand) == ERROR_MALLOC)
				return (NULL);
		}
		else if (str[index] == '$' && expand->act == CHANGE)
		{
			new_str = ft_cat_env_variable(new_str, str, &index, env);
			if (new_str == NULL)
				return (NULL);
			expand = expand->next;
		}
		else if (ft_not_replace(str, &new_str, index, &expand) == ERROR_MALLOC)
			return (NULL);
		index++;
	}
	return (new_str);
}
