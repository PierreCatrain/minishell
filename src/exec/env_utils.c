/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:09:13 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/01 21:31:20 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_str_dup_env(char *s1, char *s2)
{
	int	len;
	int	i;

	len = ft_strlen(s1);
	s2 = (char *) malloc(sizeof(char) * (len + 1));
	if (!s2)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	**dup_env(char **env)
{
	int		len_env;
	int		i;
	char	**new_env;

	if (!env)
		return (NULL);
	len_env = ft_len_tab_tab(env);
	new_env = (char **) malloc(sizeof(char *) * (len_env + 2));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_str_dup_env(env[i], new_env[i]);
		if (!new_env)
			return (NULL);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

char	**dup_env_ascii_order(char **env)
{
	int		len_env;
	int		i;
	char	**new_env;

	len_env = ft_len_tab_tab(env);
	new_env = (char **) malloc(sizeof(char *) * (len_env + 2));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_str_dup_env(env[i], new_env[i]);
		if (!new_env)
			return (NULL);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

int	ft_realloc_env(char ***env, int size)
{
	char	**cp_env;
	int		i;

	cp_env = dup_env(*env);
	free_tab_tab(*env);
	*env = malloc (sizeof(char *) * (ft_len_tab_tab(cp_env) + size + 1));
	if ((*env) == NULL)
		return (ERROR_MALLOC);
	i = 0;
	while (cp_env[i])
	{
		(*env)[i] = ft_str_dup_env(cp_env[i], (*env)[i]);
		i++;
	}
	(*env)[i] = NULL;
	free_tab_tab(cp_env);
	return (i);
}