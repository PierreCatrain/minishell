/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_env_variable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 07:05:34 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/10 18:19:55 by lgarfi           ###   ########.fr       */
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

char	**ft_add_to_2d_expand(char **base, char *add)
{
	char	**new;
	int		index;

	new = malloc((ft_strlen_2d(base) + 2) * sizeof(char *));
	if (new == NULL)
		return (free_2d(base), NULL);
	index = 0;
	while (base != NULL && base[index])
	{
		new[index] = ft_strdup(base[index]);
		if (new[index] == NULL)
			return (free_2d(base), NULL);
		index++;
	}
	new[index] = ft_strdup(add);
	if (new[index] == NULL)
		return (free_2d(base), NULL);
	new[++index] = NULL;
	if (base != NULL)
		free_2d(base);
	return (new);
}

int ft_set_split_add_expand_part1(char ***split, char **new_str, int *add_next, int *add_start)
{
	*split = ft_split(*new_str, ' ');
	if (*split == NULL)
		return (ERROR_MALLOC);
	// if ((*new_str)[0] == ' ')
	// 	*add_start = 0;
	// else
	// 	*add_start = 1;
	if ((*new_str)[0] != ' ' && *add_next != -1)
		*add_start = 1;
	else
		*add_start = 0;
	if ((*new_str)[ft_strlen(*new_str)] == ' ')
		*add_next = 0;
	else
		*add_next = 1;
	return (SUCCESS);
}

int ft_set_split_add_expand_part2(char ***new, char ***res, char **split)
{
	int index;
	
	*new = malloc(sizeof(char *));
	if (*new == NULL)
		return (free_2d(split), ERROR_MALLOC);
	(*new)[0] = NULL;
	index = -1;
	while ((*res)[++index])
	{
		*new = ft_add_to_2d_expand(*new, (*res)[index]);
		if (*new == NULL)
			return (free_2d(split), ERROR_MALLOC);
	}
	return (SUCCESS);
}

int ft_clear_buffer_in_split_expand(int index, char ***new, int add_start, char **split)
{
	int len;
	
	len = ft_strlen_2d(*new);
	if (len != 0 && index == 0 && add_start == 1)
	{
		(*new)[len - 1] = ft_strjoin_1_malloc((*new)[len - 1], split[index]);
		if ((*new)[len - 1] == NULL)
			return (free_2d(split), free_2d(*new), ERROR_MALLOC);
	}
	else
	{
		*new = ft_add_to_2d_expand(*new, split[index]);
		if (*new == NULL)
			return (free_2d(split), ERROR_MALLOC);
	}
	return (SUCCESS);
}

int ft_split_add_expand(char *new_str, char ***res, int *add_next)
{
	char **split;
	int add_start;
	int index;
	char **new;

	if (ft_set_split_add_expand_part1(&split, &new_str, add_next, &add_start) != SUCCESS)
		return (ERROR_MALLOC);
	if (ft_set_split_add_expand_part2(&new, res, split) != SUCCESS)
		return (ERROR_MALLOC);
	index = -1;
	while (split[++index])
	{
		if (ft_clear_buffer_in_split_expand(index, &new, add_start, split) != SUCCESS)
			return (ERROR_MALLOC);
	}
	free_2d(*res);
	*res = new;
	return (SUCCESS);
}

char	*ft_strjoin_1_malloc_expand(char *str1, char *str2)
{
	char	*join;
	int		i;
	int		j;

	if (str1 == NULL && str2 == NULL)
		return (NULL);
	if (str2 == NULL)
		return (ft_strdup(str1));
	if (str1 == NULL)
		return (ft_strdup(str2));
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

int ft_set_add_and_replace_env_variable(char ***res, char **new_str, char **new_args, t_data_expand *data_expand)
{
	int index;
	
	data_expand->add_next = -1;
	index = -1;
	*res = malloc(sizeof(char *));
	if (*res == NULL)
		return (ERROR_MALLOC);
	(*res)[0] = NULL;
	while (new_args[++index])
	{
		*res = ft_add_to_2d(*res, new_args[index]);
		if (res == NULL)
			return (free_2d(new_args), ERROR_MALLOC);
	}
	free_2d(new_args);
	*new_str = malloc(sizeof(char));
	if (*new_str == NULL)
		return (free_2d(*res), ERROR_MALLOC);
	(*new_str)[0] = '\0';
	data_expand->index = -1;
	return (SUCCESS);
}

int reset_the_buffer(t_data_expand *data_expand, char ***res, char **new_str)
{
	int len;
	
	if (*new_str[0] != '\0')
	{
		len = ft_strlen_2d(*res);
		if (len == 0 || data_expand->add_next != 1)
		{
			*res = ft_add_to_2d_expand(*res, *new_str);
			if (*res == NULL)
				return (free(*new_str), ERROR_MALLOC);
		}
		else
		{
			(*res)[len - 1] = ft_strjoin_1_malloc((*res)[len - 1], *new_str);
			if ((*res)[len - 1] == NULL)
				return (free_2d(*res), free(*new_str), ERROR_MALLOC);
		}
		free(*new_str);
		*new_str = malloc(sizeof(char));
		if (*new_str == NULL)
			return (free_2d(*res), ERROR_MALLOC);
		(*new_str)[0] = '\0';
		if (data_expand->add_next == -1)
			data_expand->add_next = 1;
	}
	return (SUCCESS);
}

char **end_add_and_replace(char *new_str, char ***res, t_data_expand *data_expand, char *str)
{
	int len;

	if (new_str[0] != '\0')
	{
		len = ft_strlen_2d(*res);
		if (len == 0 || data_expand->add_next != 1 || strcmp(new_str, str) == 0)
		{	
			*res = ft_add_to_2d_expand(*res, new_str);
			if (*res == NULL)
				return (free(new_str), NULL);
		}
		else
		{
			(*res)[len - 1] = ft_strjoin_1_malloc_expand((*res)[len - 1], new_str);
			if ((*res)[len - 1] == NULL)
				return (free_2d(*res), free(new_str), NULL);
		}
	}
	return (free(new_str), *res);
}

int ft_add_replace_status(t_data_expand *data_expand, char ***res, char **new_str, t_expand **expand)
{
	if (reset_the_buffer(data_expand, res, new_str) != SUCCESS)
		return (ERROR_MALLOC);
	if (rep_status(&data_expand->index, new_str, data_expand->status, expand) == ERROR_MALLOC)
		return (ERROR_MALLOC);
	if (ft_split_add_expand(*new_str, res, &data_expand->add_next) != SUCCESS)
		return (free(*new_str), free_2d(*res), ERROR_MALLOC);
	free(*new_str);
	*new_str = malloc(sizeof(char));
	if (*new_str == NULL)
		return (free_2d(*res), ERROR_MALLOC);
	(*new_str)[0] = '\0';
	return (SUCCESS);
}

int ft_add_replace_classique(t_data_expand *data_expand, char ***res, char **new_str, char *str)
{
	if (reset_the_buffer(data_expand, res, new_str) != SUCCESS)
		return (ERROR_MALLOC);
	*new_str = ft_cat_env_variable(*new_str, str, &data_expand->index, data_expand->env);
	if (*new_str == NULL)
		return (ERROR_MALLOC);
	if (ft_split_add_expand(*new_str, res, &data_expand->add_next) != SUCCESS)
	{
		return (free(*new_str), free_2d(*res), ERROR_MALLOC);
	}
	free(*new_str);
	*new_str = malloc(sizeof(char));
	if (*new_str == NULL)
		return (free_2d(*res), ERROR_MALLOC);
	(*new_str)[0] = '\0';
	return (SUCCESS);
}

char	**ft_add_and_replace_env_variable(char *str, t_expand *expand, t_data_expand *data_expand, char **new_args)
{
	if (ft_set_add_and_replace_env_variable(&data_expand->res, &data_expand->new_str, new_args, data_expand) != SUCCESS)
		return (NULL);
	while (str[++data_expand->index])
	{
		if (str[data_expand->index] == '$' && str[data_expand->index + 1] == '?' && expand->act == CHANGE)
		{
			if (ft_add_replace_status(data_expand, &data_expand->res, &data_expand->new_str, &expand) != SUCCESS)
				return (NULL);
		}
		else if (str[data_expand->index] == '$' && expand->act == CHANGE)
		{
			if (ft_add_replace_classique(data_expand, &data_expand->res, &data_expand->new_str, str) != SUCCESS)
				return (NULL);
			expand = expand->next;
		}
		else
		{
			if (ft_not_replace(str, &data_expand->new_str, data_expand->index, &expand) == ERROR_MALLOC)
				return (NULL);
		}
	}
	return (end_add_and_replace(data_expand->new_str, &data_expand->res, data_expand, str));
}
