/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 08:31:46 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/04 12:01:16 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

char **ft_add_2d_to_2d(char **base, char **add)
{
    char **new;
    int index;
    int index_2;

    new = malloc((ft_strlen_2d(base) + ft_strlen_2d(add) + 1) * sizeof(char *));
    if (new == NULL)
        return (NULL);
    index = 0;
    while (base[index])
    {
        new[index] = ft_strdup(base[index]);
        if (new[index] == NULL)
            return (NULL);//free le debut de la dup
        index++;
    }
    index_2 = 0;
     while (add[index_2])
    {
        new[index + index_2] = ft_strdup(add[index_2]);
        if (new[index + index_2] == NULL)
            return (NULL);//free le debut de la dup
        index_2++;
    }
    new[++index] = NULL;
    return (new);
}

char **ft_add_to_2d(char **base, char *add)
{
    char **new;
    int index;

    new = malloc((ft_strlen_2d(base) + 2) * sizeof(char *));
    if (new == NULL)
        return (NULL);
    index = 0;
    while (base != NULL && base[index])
    {
        new[index] = ft_strdup(base[index]);
        if (new[index] == NULL)
            return (NULL);//free le debut de la dup
        index++;
    }
    new[index] = ft_strdup(add);
    if (new[index] == NULL)
        return (NULL);//free le debut de la dup
    new[++index] = NULL;
	if (base != NULL)
		free_2d(base);
    return (new);
}

int	ft_strchr_wildcard(char *str, char *find)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i + j] == find[j])
		{
			j++;
			if (j == ft_strlen(find))
				return (i + j);
		}
		i++;
		if (i > ft_strlen(str) - ft_strlen(find))
			return (0);
	}
	return (0);
}

int ft_check_all(char **split, char *str)
{
	int index_split;
	int index_str;
	int tmp;
	int len_str;
	
	len_str = ft_strlen(str);
	index_split = 0;
	index_str = 0;
	while (split[index_split] && index_str < len_str)
	{
		tmp = ft_strchr_wildcard(str, split[index_split++]);
		if (tmp == 0)
			return (0);
		index_str += tmp;
	}
	if (split[index_split] != NULL)
		return (0);
	return (1);
}

int ft_check_before(char *to_find, char **split, char *str)
{
	if (to_find[0] == '*')
		return (1);
	if (ft_strncmp(split[0], str, ft_strlen(split[0])))
		return (0);
	return (1);
}

int ft_check_after(char *to_find, char **split, char *str)
{
	int index;

	if (to_find[ft_strlen(to_find) - 1] == '*')
		return (1);
	index = ft_strlen(str) - ft_strlen(split[ft_strlen_2d(split) - 1]);
	if (index < 0)
		return (0);
	if (ft_strncmp(split[ft_strlen_2d(split) - 1], &str[index], ft_strlen(split[ft_strlen_2d(split) - 1])))
		return (0);
	return (1);
}

char **ft_add_wildcard(char **base, char *add, t_wildcard *ls)
{
    char **new;
    char **split;
    int found;

    found = 0;
    new = NULL;
    if (ft_occ(add, '*') == 0)
	{
		new = ft_add_to_2d(base, add);
		if (new == NULL)
			return (free(add), NULL);
        return (free(add), new);
	}
	split = ft_split(add, '*');
	if (split == NULL)
		return (NULL);
	while (ls->next != NULL)
	{
		if (ft_check_before(add, split, ls->str) && ft_check_after(add, split, ls->str) && ft_check_all(split, ls->str))
		{
            if (found == 0)
            {
                new = ft_add_to_2d(base, ls->str);
		        if (new == NULL)
			        return (free_2d(split), NULL);
            }
            else
            {
                new = ft_add_to_2d(new, ls->str);
                if (new == NULL)
                    return (free_2d(split), NULL);         
            }
			found = 1;
		}
		ls = ls->next;
	}
	free_2d(split);
	if (found == 0)
	{
		new = ft_add_to_2d(base, add);
		if (new == NULL)
			return (free(add), NULL);
		free(add);
	}
    return (new);
}