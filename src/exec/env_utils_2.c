/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:37:17 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/06 19:09:16 by lgarfi           ###   ########.fr       */
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

	printf("nb dans itoa %d\n", nb);
	if (nb >= 999)
	{
		ft_putstr_fd("bash: warning: shell level (1000)"
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

int	ft_atoi_int_shlvl_main(char *nb)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	if (nb[0] == '+')
		i++;
	while (nb[i])
	{
		if (nb[i] < '0' || nb[i] > '9')
			return (0);
		i++;
	}
	i = 0;
	while (nb[i])
	{
		if (nb[i] < '0' || nb[i] >  '9')
			return (0);
		res = res * 10 + nb[i] - 48;
		i++;
	}
	res += 1;
	return (res);
}

char	*ft_change_shlvl(char *shlvl)
{
	char	*res_val;
	char	*res;

	res_val = ft_itoa_shlvl(ft_atoi_int_shlvl_main(shlvl));
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
	*env = malloc (sizeof(char *) * (len_envp + 2));
	if (!(*env))
		return (ERROR_MALLOC);
	if (getenv("PATH") == NULL)
		(*env)[++(*i)] = ft_get_path();
	if ((*env)[(*i)] == NULL)
		return (ERROR_MALLOC);
	return (0);
}

char	**ft_copy_env(char **envp)
{
	char	**env;
	int		len_envp;
	int		i;
	char	*envp_name;

	len_envp = ft_strlen_2d(envp);
	i = -1;
	ft_get_path_in_env(envp, &env, &i);
	if (!envp[0])
		return (env);
	while (envp[++i])
	{
		envp_name = ft_find_export_name(envp[i]);
		if (ft_strcmp(envp_name, "SHLVL") == 0)
		{
			env[i] = ft_change_shlvl(getenv("SHLVL"));
			free(envp_name);
			continue ;
		}
		free(envp_name);
		env[i] = ft_str_dup_env(envp[i], env[i]);
	}
	env[i] = NULL;
	return (env);
}

// int	main(int ac, char **av, char **envp)
// {
// 	char **env;
	
// 	(void)ac;
// 	(void)av;
	
// 	env = ft_copy_env(envp);
// 	print_tab_tab(env);
// 	free_tab_tab(env);
// 	return (0);
// }