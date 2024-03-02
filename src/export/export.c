/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 22:51:52 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/02 14:21:37 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export3(char *export_str, char **export, int *res)
{
	int		empty;

	*res = 0;
	if (export_str[0] == '=' || !ft_check_export_name(export_str))
	{
		printf("bash: export:= `%s': not a valid identifier\n", export_str);
		*res = 2;
		return ;
	}
	if (!ft_export_name(export_str, export) || !ft_is_ascii(export_str[0]))
	{
		printf("export:= not valid in this context: %s\n", *export);
		*res = 2;
		return (free(*export));
	}
	if (!check_after_equal(*export))
	{
		empty = ft_check_empty_export(*export);
		if (empty == 1)
			*export = add_equal_null_char(*export);
		else if (empty == 2)
			*export = add_null(*export);
	}
}

int	ft_export2(char ***env, char *export_str)
{
	char	*export;
	int		i;
	int		res;

	ft_export3(export_str, &export, &res);
	if (res != 0)
		return (res);
	if (ft_is_export_in_env(*env, export))
	{
		ft_change_export(env, export);
		return (free(export), 0);
	}
	// printf("env[avant realloc]\n\n\n");
	// print_tab_tab(*env);
	// printf("env[apres realloc]\n\n\n");
	// print_tab_tab(*env);
	i = ft_realloc_env(env, 1);
	(*env)[i] = ft_str_dup_env(export, (*env)[i]);
	(*env)[i + 1] = NULL;
	free(export);
	return (0);
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
		return (0);
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