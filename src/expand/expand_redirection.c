/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 06:57:07 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/04 19:39:22 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_ambiguous_redirect(char *str, char **split, char *new)
{
	int	index;

	index = -1;
	while (split[++index])
		free(split[index]);
	free(split);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
	free(str);
	free(new);
	return (NULL);
}

char	*ft_find_wildcard(char *str, t_wildcard *ls, char **split, int found)
{
	char	*new;

	while (ls != NULL)
	{
		if (ft_check_before(str, split, ls->str) && ft_check_after(str, \
					split, ls->str) && ft_check_all(split, ls->str))
		{
			if (found == 0)
			{
				new = ft_strdup(ls->str);
				if (new == NULL)
					return (free_2d(split), free(str), NULL);
			}
			else
				return (ft_ambiguous_redirect(str, split, new));
			found++;
		}
		if (ls->next != NULL)
			ls = ls->next;
		else
			break ;
	}
	if (found == 0)
		return (free_2d(split), str);
	return (free_2d(split), free(str), new);
}

char	*ft_transfo_wildcard(char *str, t_wildcard *ls)
{
	char	**split;

	if (ft_occ(str, '*') == 0)
	{
		return (str);
	}
	split = ft_split(str, '*');
	if (split == NULL)
		return (free(str), NULL);
	return (ft_find_wildcard(str, ls, split, 0));
}

char	*transfo_expand(char *str, t_expand *expand, t_data_parse *data_parse)
{
	t_wildcard	*ls;
	char		*new;

	ls = NULL;
	new = ft_replace_env_variable(str, expand, data_parse->env, \
			data_parse->exit_status);
	if (new == NULL)
		return (NULL);
	if (set_ls(&ls) != SUCCESS)
		return (NULL);
	new = ft_transfo_wildcard(new, ls);
	if (new == NULL)
		return (ft_free_wildcard(&ls), free_expand(data_parse->expand, \
					ft_strlen_2d(data_parse->args_tmp)), \
				free_2d(data_parse->args_tmp), NULL);
	return (ft_free_wildcard(&ls), new);
}
