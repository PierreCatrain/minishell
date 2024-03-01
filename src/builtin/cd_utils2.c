/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 21:21:48 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/01 21:22:35 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_msg_err_getcwd(void)
{
	ft_putstr_fd("sh: 0 : getcwd() failed: No such file or directory\n", 2);
}

int	ft_get_env_value2(char **env_name, char *env, char *str, char **env_value)
{
	int	j;
	int	k;
	int	len;

	j = 0;
	k = 0;
	*env_name = ft_find_export_name(env);
	if (ft_strcmp(*env_name, str) == 0)
	{
		printf("comparaison trouve env name %s\n str %s\n", *env_name, str);
		len = ft_strlen(env) - ft_strlen(*env_name) - 1;
		printf("1\n");
		free(*env_name);
		printf("1\n");
		while (env[j] && env[j] != '=')
			j++;
		k = 0;
		*env_value = malloc(len + 1);
		while (env[++j])
			(*env_value)[k++] = env[j];
		(*env_value)[k] = '\0';
		return (0);
	}
	return (1);
}

char	*ft_get_env_value(char **env, char *str)
{
	int		i;
	char	*env_value;
	char	*env_name;

	i = -1;
	env_value = NULL;
	while (env[++i])
	{
		if (ft_get_env_value2(&env_name, env[i], str, &env_value) == 1)
			free(env_name);
		else
			return (env_value);
	}
	return (NULL);
}
