/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:01:18 by lgarfi            #+#    #+#             */
/*   Updated: 2024/02/18 17:50:21 by lgarfi           ###   ########.fr       */
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

char	**ft_copy_env_exept_unset(char **env, int unset_index)
{
	int	i;
	char	**new_env;

	i = -1;
	new_env = (char **) malloc(sizeof(char *) * ft_len_tab_tab(env));
	while (++i < unset_index)
	{
		new_env[i] = ft_str_dup_env(env[i], new_env[i]);
		if (!new_env[i])
		{
			return (NULL);
			// gestion d'erreur
		}
	}
	while (env[++i])
	{
		new_env[i - 1] = ft_str_dup_env(env[i], new_env[i - 1]);
		if (!new_env[i - 1])
		{
			return (NULL);
			// gestion d'erreur
		}
	}
	new_env[i] = NULL;
	// free ancien env
	return (new_env);
}

int	ft_unset_is_in_env(char **env, char *unset_str)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		printf("env[%d] = %s | unset_Str = %s\n", i, env[i], unset_str);
		if (ft_strcmp(env[i], unset_str) == 0)
		{
			printf("trouve\n");
			return (1);
		}
	}
	printf("pas trouve\n");
	return (0);
}

void	ft_unset(char ***env, char *unset_str)
{
	int	unset_index;

	if (!unset_str)
		return ;
	else if (unset_str[0] == '\0')
		return ;
	if (ft_unset_is_in_env(*env, unset_str) == 0)
		return ;
	unset_index = ft_find_unset_index(*env, unset_str);
	if (unset_index == -1)
		return ;
	*env = ft_copy_env_exept_unset(*env, unset_index);
	return ;
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
