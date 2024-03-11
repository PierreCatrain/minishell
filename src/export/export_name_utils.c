/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_name_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:10:21 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/11 01:23:17 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_export_name(char *str)
{
	int				i;
	int				j;
	static char		except[25] = "!\\[]@#$%^&*-()+=/?.,`~\" ";

	j = 0;
	while (except[j])
	{
		i = 0;
		while (str[i] && str[i] != '=')
		{
			if (str[i] == except[j])
				return (0);
			i++;
		}
		j++;
	}
	return (1);
}

void	ft_add_export_value(char **export, char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i + 1] != '=')
		i++;
	while (str[i])
	{
		(*export)[i] = str[i];
		i++;
	}
	(*export)[i] = '\0';
}

int	ft_is_export_in_env(char **env, char *str)
{
	char	*export_name;
	int		i;
	int		len_str;

	export_name = ft_find_export_name(str);
	if (!export_name)
		return (-1);
	i = 0;
	len_str = ft_strlen(export_name);
	while (env[i] != NULL)
	{
		if (ft_strncmp(str, env[i], len_str) == 0)
		{
			free(export_name);
			return (i);
		}
		i++;
	}
	free(export_name);
	return (0);
}

void	ft_change_export(char ***env, char *str)
{
	int	index_export;
	int	i;

	index_export = ft_find_export_index(*env, str);
	if (index_export == -1)
		return ;
	i = 0;
	while (i < index_export)
		i++;
	free((*env)[i]);
	(*env)[i] = ft_str_dup_env(str, (*env)[i]);
}

int	ft_find_export_index(char **env, char *str)
{
	int		i;
	int		len_str;
	char	*export_name;

	i = 0;
	export_name = ft_find_export_name(str);
	len_str = ft_strlen(export_name);
	if (len_str == 1)
		len_str += 1;
	while (env[i])
	{
		if (ft_strncmp(env[i], str, len_str -1) == 0)
		{
			free(export_name);
			return (i);
		}
		i++;
	}
	free(export_name);
	return (-1);
}
