/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_wildcard_4.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 22:09:52 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/02 06:14:35 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_strjoin_1_malloc(char *str1, char *str2)
{
	char	*join;
	int		i;
	int		j;

	if (str2 == NULL)
		return (str1);
	join = malloc ((ft_strlen(str1) + ft_strlen(str2) + 1) * sizeof(char));
	if (join == NULL)
		return (free(str1), NULL);
	i = -1;
	while (str1[++i])
		join[i] = str1[i];
	j = -1;
	while (str2[++j])
		join[i + j] = str2[j];
	join[i + j] = '\0';
	return (free(str1), join);
}

t_wildcard	*ft_lst_wildcard_new(char *str)
{
	t_wildcard	*new;

	new = malloc(sizeof(t_wildcard));
	if (new == NULL)
		return (NULL);
	new->prev = NULL;
	new->next = NULL;
	new->str = ft_strdup(str);
	if (new->str == NULL)
		return (free(new), NULL);
	return (new);
}

t_wildcard	*ft_lst_wildcard_last(t_wildcard *ls)
{
	while (ls->next != NULL)
		ls = ls->next;
	return (ls);
}

int	ft_lst_wildcard_add_back(t_wildcard **ls, t_wildcard *new)
{
	if (new == NULL)
		return (ERROR_MALLOC);
	if (*ls == NULL)
	{
		*ls = new;
		return (SUCCESS);
	}
	new->prev = ft_lst_wildcard_last(*ls);
	ft_lst_wildcard_last(*ls)->next = new;
	return (SUCCESS);
}

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
