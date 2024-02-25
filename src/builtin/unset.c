/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:01:18 by lgarfi            #+#    #+#             */
/*   Updated: 2024/02/24 17:39:35 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	ft_find_unset_index(char **env, char *unset_str)
{
	int	i;
	int	finded;

	i = 0;
	finded = 0;
	while (env[i])
	{
		if (ft_strcmp(ft_find_export_name(env[i]), unset_str) == 0)
		{
			finded = 1;
			break ;
		}
		i++;
	}
	if (finded == 1)
		return (i);
	return (-1);
}

int	ft_copy_env_exept_unset(char **env, int unset_index)
{
	int		i;
	char	**new_env;

	i = -1;
	new_env = (char **) malloc(sizeof(char *) * ft_len_tab_tab(env));
	if (!new_env)
		return (ERROR_MALLOC);
	while (++i < unset_index)
	{
		new_env[i] = ft_str_dup_env(env[i], new_env[i]);
		if (!new_env[i])
		{
			return (ERROR_MALLOC);
			// gestion d'erreur
		}
	}
	while (env[++i])
	{
		new_env[i - 1] = ft_str_dup_env(env[i], new_env[i - 1]);
		if (!new_env[i - 1])
		{
			return (ERROR_MALLOC);
			// gestion d'erreur
		}
	}
	new_env[i] = NULL;
	return (0);
}

int	ft_unset_is_in_env(char **env, char *unset_str)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (ft_strcmp(env[i], unset_str) == 0)
		{
			return (1);
		}
	}
	return (0);
}

int	ft_unset(char ***env, char *unset_str)
{
	int	unset_index;
	int	status;

	if (!unset_str)
		return (0);
	else if (unset_str[0] == '\0')
		return (0);
	if (ft_unset_is_in_env(*env, unset_str) == 0)
		return (0);
	unset_index = ft_find_unset_index(*env, unset_str);
	if (unset_index == -1)
		return (0);
	status = ft_copy_env_exept_unset(*env, unset_index);
	if (ft_realloc_env(env, -1) == ERROR_MALLOC)
		return (ERROR_MALLOC);
	return (status);
}

// int main(int ac, char **av, char **env)
// {
// 	char	**new_env;

// 	new_env = ft_unset(env, av[1]);
// 	if (!new_env)
// 		return (0);
// 	// print_tab_tab(new_env);
// 	// free_tab_tab(new_env);
// 	return (0);
// }
