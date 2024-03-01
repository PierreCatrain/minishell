/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 22:51:52 by lgarfi            #+#    #+#             */
/*   Updated: 2024/02/29 19:40:37 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export2(char ***env, char *export_str)
{
	char	*export = NULL;
	int		i;
	int		empty;


	if (export_str[0] == '=' || !ft_check_export_name(export_str))
	{
		printf("bash: export:= `%s': not a valid identifier\n", export_str);
		return (2);
		// gestion d'erreur
	}
	if (!ft_export_name(export_str, &export) || !ft_is_ascii(export_str[0]))
	{
		
		printf("export:= not valid in this context: %s\n", export);
		free(export);
		return (2);
	}
	if (!check_after_equal(export))
	{
		empty = ft_check_empty_export(export);
		if (empty == 1)
			export = add_equal_null_char(export);
		else if (empty == 2)
			export = add_null(export);
	}
	if (ft_is_export_in_env(*env, export))
	{
		ft_change_export(env, export);
		{
			free(export);
			return (0);
		}
	}
	i = ft_realloc_env(env, 1);
	(*env)[i] = ft_str_dup_env(export, (*env)[i]);
	(*env)[i + 1] = NULL;
	free(export);
	return(0);
}

int	ft_export(char ***env, char **arg, int free)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	if (!arg[1])
	{
		ft_print_env_ascii_order(*env);
		return (0); // gestion d'erreur
	}
	while (arg[i])
	{
		status = ft_export2(env, arg[i]);
		i++;
	}
	if (free)
		free_tab_tab(arg);
	return (status);
}

// ajouter l'export de plusieur choix possible export a=qwer b=qwer ... (voir sil y a des cas d'erreurs)

// int	main(int ac, char **av, char **envp)
// {
// 	char	**env;

// 	env = dup_env(envp);
// 	(void)ac;
// 	ft_export(&env, av, 0);
// 	if (!env)
// 		return (0);
// 	print_tab_tab(env);
// 	free_tab_tab(env);
// 	return (0);
// }

//ft_error to do