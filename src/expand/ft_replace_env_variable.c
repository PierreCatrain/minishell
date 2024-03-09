/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_env_variable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 07:05:34 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/09 21:40:52 by picatrai         ###   ########.fr       */
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

int ft_split_add_expand(char *new_str, char ***res, int *add_next)
{
	char **split;
	int add_start;
	int index;
	char **new;
	int len;

	split = ft_split(new_str, ' ');
	if (split == NULL)
		return (ERROR_MALLOC);
	if (new_str[ft_strlen(new_str)] == ' ')
		*add_next = 0;
	else
		*add_next = 1;
	if (new_str[0] == ' ')
		add_start = 0;
	else
		add_start = 1;
	new = malloc(sizeof(char *));
	if (new == NULL)
		return (free_2d(split), ERROR_MALLOC);
	new[0] = NULL;
	index = -1;
	while ((*res)[++index])
	{
		new = ft_add_to_2d_expand(new, *res[index]);
		if (new == NULL)
			return (free_2d(split), ERROR_MALLOC);
	}
	index = -1;
	while (split[++index])
	{
		len = ft_strlen_2d(new);
		if (len != 0 && index == 0 && add_start == 1)
		{
			new[len - 1] = ft_strjoin_1_malloc(new[len - 1], split[index]);
			if (new[len - 1] == NULL)
				return (free_2d(split), free_2d(new), ERROR_MALLOC);
		}
		else
		{
			new = ft_add_to_2d_expand(new, split[index]);
			if (new == NULL)
				return (free_2d(split), ERROR_MALLOC);
		}
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

char	**ft_add_and_replace_env_variable(char *str, t_expand *expand, t_data_expand *data_expand, char **new_args)
{
	char **res;
	char	*new_str;
	int		index;
	int len;

	data_expand->add_next = 1;
	index = -1;
	res = malloc(sizeof(char *));
	if (res == NULL)
		return (NULL);
	res[0] = NULL;
	while (new_args[++index])
	{
		res = ft_add_to_2d(res, new_args[index]);
		if (res == NULL)
			return (free_2d(new_args), NULL);
	}
	free_2d(new_args);
	index = 0;
	new_str = malloc(sizeof(char));
	if (new_str == NULL)
		return (free_2d(res), NULL);
	new_str[0] = '\0';
	while (str[index])
	{
		if (str[index] == '$' && str[index + 1] == '?' && expand->act == CHANGE)
		{
			if (new_str[0] != '\0')
			{
				len = ft_strlen_2d(res);
				if (len == 0 || data_expand->add_next == 0)
				{
					res = ft_add_to_2d_expand(res, new_str);
					if (res == NULL)
						return (free(new_str), NULL);
				}
				else
				{
					res[len - 1] = ft_strjoin_1_malloc(res[len - 1], new_str);
					if (res[len - 1] == NULL)
						return (free_2d(res), free(new_str), NULL);
				}
				free(new_str);
				new_str = malloc(sizeof(char));
				if (new_str == NULL)
					return (free_2d(res), NULL);
				new_str[0] = '\0';
			}
			if (rep_status(&index, &new_str, data_expand->status, &expand) == ERROR_MALLOC)
				return (NULL);
			if (ft_split_add_expand(new_str, &res, &data_expand->add_next) != SUCCESS)
				return (free(new_str), free_2d(res), NULL);
			free(new_str);
			new_str = malloc(sizeof(char));
			if (new_str == NULL)
				return (free_2d(res), NULL);
			new_str[0] = '\0';
		}
		else if (str[index] == '$' && expand->act == CHANGE)
		{
			if (new_str[0] != '\0')
			{
				len = ft_strlen_2d(res);
				if (len == 0 || data_expand->add_next == 0)
				{
					res = ft_add_to_2d_expand(res, new_str);
					if (res == NULL)
						return (free(new_str), NULL);
				}
				else
				{
					res[len - 1] = ft_strjoin_1_malloc(res[len - 1], new_str);
					if (res[len - 1] == NULL)
						return (free_2d(res), free(new_str), NULL);
				}
				free(new_str);
				new_str = malloc(sizeof(char));
				if (new_str == NULL)
					return (free_2d(res), NULL);
				new_str[0] = '\0';
			}
			new_str = ft_cat_env_variable(new_str, str, &index, data_expand->env);
			if (new_str == NULL)
				return (NULL);
			if (ft_split_add_expand(new_str, &res, &data_expand->add_next) != SUCCESS)
				return (free(new_str), free_2d(res), NULL);
			free(new_str);
			new_str = malloc(sizeof(char));
			if (new_str == NULL)
				return (free_2d(res), NULL);
			new_str[0] = '\0';
			expand = expand->next;
		}
		else if (ft_not_replace(str, &new_str, index, &expand) == ERROR_MALLOC)
			return (NULL);
		index++;
	}
	if (new_str[0] != '\0')
	{
		len = ft_strlen_2d(res);
		if (len == 0 || data_expand->add_next == 0 || strcmp(new_str, str) == 0)
		{	
			res = ft_add_to_2d_expand(res, new_str);
			if (res == NULL)
				return (free(new_str), NULL);
		}
		else
		{
			res[len - 1] = ft_strjoin_1_malloc_expand(res[len - 1], new_str);
			if (res[len - 1] == NULL)
				return (free_2d(res), free(new_str), NULL);
		}
	}
	return (free(new_str), res);
}
