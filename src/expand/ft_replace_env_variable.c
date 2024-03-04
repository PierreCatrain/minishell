/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_env_variable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 07:05:34 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/04 17:55:16 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int ft_size_malloc_long_long(long long nb)
{
	int count;

	count = 0;
	if (nb >= 0 && nb <= 9)
		return (1);
	if (nb < 0)
	{
		nb *= -1;
		count++;
	}
	while (nb > 0)
	{
		count++;
		nb /= 10;
	}
	return (count);
}

char *ft_itoa_long_long(long long nb)
{
	char *str;
	int count;
	int index;
	
	count = ft_size_malloc_long_long(nb);
	str = malloc ((count + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	index = count - 1;
	while (index >= 0)
	{
		str[index--] = (nb % 10) + 48;
		nb /= 10;
	}
	str[count] = '\0';
	return (str);	
}

char *ft_str_cat_long_long(char *new_str, long long g_exit_status)
{
	char *exit;
	char *cat;
	int i;
	int j;
	
	exit = ft_itoa_long_long(g_exit_status);
	if (exit == NULL)
		return (free(new_str), NULL);
	cat = malloc ((ft_strlen(new_str) + ft_strlen(exit) + 1) * sizeof(char));
	if (cat == NULL)
		return (free(exit), free(new_str), NULL);
	i = -1;
	while (new_str[++i])
		cat[i] = new_str[i];
	j = -1;
	while (exit[++j])
		cat[i + j] = exit[j];
	cat[i + j] = '\0';
	return (free(exit), free(new_str), cat);
}

char *ft_replace_env_variable(char *str, t_expand *expand, int status)
{
    int index;
    char *new_str;

    index = 0;
    new_str = malloc(sizeof(char));
    if (new_str == NULL)
        return (NULL);
    new_str[0] = '\0';
    while (str[index])
    {
        if (str[index] == '$' && str[index + 1] == '?' && expand->action == CHANGE)
        {
            index++;
            new_str = ft_str_cat_long_long(new_str, status);
            if (new_str == NULL)
                return (NULL);
            expand = expand->next;
        }
        else if (str[index] == '$' && str[index + 1] == '?' && expand->action == KEEP)
        {
            new_str = ft_join_char(new_str, str[index]);
            if (new_str == NULL)
                return (NULL);
            expand = expand->next;
        }
        else if (str[index] == '$' && expand->action == CHANGE)
        {
            new_str = ft_cat_env_variable(new_str, str, &index);
            if (new_str == NULL)
                return (NULL);
            expand = expand->next;
        }
        else if (str[index] == '$' && expand->action == KEEP)
        {
            new_str = ft_join_char(new_str, str[index]);
            if (new_str == NULL)
                return (NULL);
            expand = expand->next;
        }
        else
        {
            new_str = ft_join_char(new_str, str[index]);
            if (new_str == NULL)
                return (NULL);
        }
        index++;
    }
    return (new_str);
}