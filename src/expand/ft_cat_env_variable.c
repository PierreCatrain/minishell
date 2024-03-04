/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cat_env_variable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 07:36:28 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/04 18:37:56 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_lim_isolate(char *str, int index)
{
	index++;
	while (ft_isalphanum(str[index]))
		index++;
	return (index);		
}

char	*ft_str_isolate(char *str, int index_debut, int index_fin)
{
	char	*new_str;
	int	index_new_str;

	index_debut++;
	new_str = malloc((index_fin - index_debut + 1) * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	index_new_str = 0;
	while (index_debut + index_new_str < index_fin)
	{
		new_str[index_new_str] = str[index_debut + index_new_str];
		index_new_str++;
	}
	new_str[index_new_str] = '\0';
	return (new_str);
}

char *ft_add_env(char *str, char *new_str, int index, char **env)
{
	char *str_isolate;

	str_isolate = ft_str_isolate(str, index, ft_lim_isolate(str, index));
	if (str_isolate == NULL)
		return (free(new_str), NULL);
	new_str = ft_strjoin_1_malloc(new_str, ft_get_env_value(env, str_isolate));
	if (new_str == NULL)
		return (free(str_isolate), NULL);
	return (free(str_isolate), new_str);
}

char *ft_cat_env_variable(char *new_str, char *str, int *index, char **env)
{
    new_str = ft_add_env(str, new_str, *index, env);
    if (new_str == NULL)
        return (NULL);
    *index = ft_lim_isolate(str, *index) - 1;
	return (new_str);
}