/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:37:17 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/10 21:30:00 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_word(int nb)
{
	int	count;

	count = 1;
	while (nb >= 10)
	{
		nb /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa_shlvl(int nb)
{
	char	*str;
	int		len;
	int		i;

	if (nb >= 999)
	{
		ft_putstr_fd("minishell: warning: shell level (1000)"
			" too high, resetting to 1\n", 2);
		nb = 1;
	}
	len = count_word(nb);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	str[len] = '\0';
	while (0 < len)
	{
		str[len - 1] = (nb % 10) + '0';
		nb /= 10;
		len--;
	}
	return (str);
}

void	ft_check_increment(int *res)
{
	char	*last_cmd;

	last_cmd = getenv("_");
	if (ft_strcmp(last_cmd, "./minishell") == 0)
		(*res)++;
	else
		return ;
}

int	ft_atoi_int_shlvl_main(char **envp, char *nb)
{
	int		i;
	int		res;

	i = 0;
	res = 0;
	(void)envp;
	if (nb == NULL)
		return (1);
	while (nb[i])
	{
		res = res * 10 + nb[i] - 48;
		i++;
	}
	ft_check_increment(&res);
	return (res);
}

char	*ft_change_shlvl(char **envp, char *shlvl)
{
	char	*res_val;
	char	*res;

	res_val = ft_itoa_shlvl(ft_atoi_int_shlvl_main(envp, shlvl));
	if (!res_val)
		return (NULL);
	res = ft_strjoin_wihtout_free("SHLVL=", res_val);
	free(res_val);
	if (!res)
		return (NULL);
	return (res);
}

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
	if (getenv("SHLVL") == NULL)
	{
		env_val = ft_strdup("SHLVL=1");
		ft_realloc_env(env, 1);
		(*env)[(*i)++] = ft_strdup(env_val);
		free(env_val);
		(*env)[*i] = NULL;
	}
}

char	**ft_copy_env(char **envp)
{
	char	**env;
	int		len_envp;
	int		i;
	char	*envp_name;

	len_envp = ft_strlen_2d(envp);
	i = 0;
	ft_get_path_in_env(envp, &env, &i);
	if (!env)
		return (NULL);
	if (!envp[0])
	{
		ft_check_missing_env(&env, &i);
		return (env);
	}
	while (envp[i])
	{
		envp_name = ft_find_export_name(envp[i]);
		if (ft_strcmp(envp_name, "SHLVL") == 0)
		{
			env[i] = ft_change_shlvl(envp, getenv("SHLVL"));
			free(envp_name);
			i++;
			continue ;
		}
		free(envp_name);
		env[i] = ft_str_dup_env(envp[i], env[i]);
		i++;
	}
	ft_check_missing_env(&env, &i);
	env[i] = NULL;
	return (env);
}
