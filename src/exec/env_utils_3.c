/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 01:26:47 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/11 16:19:01 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_path_in_env(char **envp, char ***env, int *i)
{
	int	len_envp;

	len_envp = ft_strlen_2d(envp);
	if (getenv("PATH") == NULL)
		len_envp = ft_strlen_2d(envp) + 1;
	*env = malloc (sizeof(char *) * (len_envp + 1));
	if (!(*env))
		return (ERROR_MALLOC);
	if (getenv("PATH") == NULL)
	{
		(*env)[(*i)] = ft_get_path();
		if ((*env)[(*i)] == NULL)
			return (free_tab_tab(*env), ERROR_MALLOC);
		(*env)[++(*i)] = NULL;
	}
	return (0);
}

void	ft_check_missing_env_2(char **env_val, char ***env, int *i)
{
	if (getenv("SHLVL") == NULL)
	{
		*env_val = ft_strdup("SHLVL=1");
		ft_realloc_env(env, 1);
		(*env)[(*i)++] = ft_strdup(*env_val);
		free(*env_val);
		(*env)[*i] = NULL;
	}
}

void	ft_check_missing_env(char ***env, int *i)
{
	char	buff[PATH_MAX + 1];
	char	*env_val;

	if (getenv("PWD") == NULL)
	{
		(*env)[(*i)] = NULL;
		env_val = ft_strjoin("PWD=", getcwd(buff, PATH_MAX));
		ft_realloc_env(env, 1);
		(*env)[(*i)] = ft_strdup(env_val);
		free(env_val);
		(*env)[++(*i)] = NULL;
	}
	if (getenv("_") == NULL)
	{
		env_val = ft_strdup("_=./minishell");
		ft_realloc_env(env, 1);
		(*env)[(*i)++] = ft_strdup(env_val);
		free(env_val);
		(*env)[*i] = NULL;
	}
	ft_check_missing_env_2(&env_val, env, i);
}
