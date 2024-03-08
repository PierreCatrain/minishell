/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 08:31:46 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/05 11:21:35 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_ls(t_wildcard **ls)
{
	struct dirent	*entry;
	DIR				*directory;

	directory = opendir(".");
	if (directory == NULL)
	{
		printf("minishell: opendir failed\n");
		return (ERROR);
	}
	while (1)
	{
		entry = readdir(directory);
		if (entry == NULL)
			break ;
		if (ft_lst_wildcard_add_back(ls, \
		ft_lst_wildcard_new(entry->d_name)) != SUCCESS)
		{
			closedir(directory);
			return (ft_print_error_malloc(), ERROR_MALLOC);
		}
	}
	closedir(directory);
	return (SUCCESS);
}

int	ft_set_add_wildcard(char ***split, char *add, char ***new)
{
	*new = NULL;
	*split = ft_split(add, '*');
	if (*split == NULL)
		return (ERROR_MALLOC);
	return (SUCCESS);
}

char	**ft_no_wildcard(char *add, char **base)
{
	char	**new;

	new = ft_add_to_2d(base, add);
	if (new == NULL)
		return (free(add), NULL);
	return (free(add), new);
}

int	ft_condition_wildcard(int *found, char **base, char ***new, t_wildcard *ls)
{
	if (*found == 0)
	{
		*new = ft_add_to_2d(base, ls->str);
		if (*new == NULL)
			return (ERROR_MALLOC);
	}
	else
	{
		*new = ft_add_to_2d(*new, ls->str);
		if (*new == NULL)
			return (ERROR_MALLOC);
	}
	*found = 1;
	return (SUCCESS);
}

char	**ft_add_wildcard(char **base, char *add, t_wildcard *ls, int found)
{
	char	**new;
	char	**split;

	if (ft_occ(add, '*') == 0)
		return (ft_no_wildcard(add, base));
	if (ft_set_add_wildcard(&split, add, &new) == ERROR_MALLOC)
		return (NULL);
	while (ls->next != NULL)
	{
		if (ft_check_before(add, split, ls->str) && ft_check_after(add, split, \
					ls->str) && ft_check_all(split, ls->str))
		{
			if (ft_condition_wildcard(&found, base, &new, ls) == ERROR_MALLOC)
				return (free_2d(split), NULL);
		}
		ls = ls->next;
	}
	if (found == 0)
	{
		new = ft_add_to_2d(base, add);
		if (new == NULL)
			return (free(add), free_2d(split), NULL);
		free(add);
	}
	return (free_2d(split), new);
}
