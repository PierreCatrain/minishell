/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 22:51:52 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/06 19:30:32 by lgarfi           ###   ########.fr       */
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

char	*ft_get_export_value(char *str)
{
	int	i;
	int	j;
	char	*export_value;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '=')
		i++;
	while (str[j])
		j++;
	export_value = malloc(j + 1);
	if (!export_value)
		return (NULL);
	j = 0;
	while (str[++i])
	{
		export_value[j] = str[i];
		j++;
	}
	export_value[j] = '\0';
	return (export_value);
}

int	ft_check_shlvl_export(char ***env, char *export_str)
{
	int		i;
	char	*export_name;
	char	*export_value;

	export_name = ft_find_export_name(export_str);
	if (!export_name)
		return (ERROR_MALLOC);
	printf("export name %s\n", export_name);
	if (ft_strcmp(export_name, "SHLVL") != 0)
		return (2);
	i = 0;
	free(export_name);
	while ((*env)[i])
	{
		printf("(*env)[i] %s\n", (*env)[i]);
		export_name = ft_find_export_name((*env)[i]);
		if (ft_strcmp(export_name, "SHLVL") == 0)
		{
			export_value = ft_get_export_value(export_str);
			printf("export value = %s\n", export_value);
			printf("env[i] que je free = %s\n", (*env)[i]);
			free((*env)[i]);
			(*env)[i] = ft_change_shlvl_export(export_value);
			free(export_value);
			free(export_name);
			return (0);
		}
		free(export_name);
		i++;
	}
	return (2);
}

int	ft_export2(char ***env, char *export_str)
{
	char	*export;
	int		i;
	int		res;

	printf("export str = %s\n", export_str);
	if (ft_check_shlvl_export(env, export_str) == 0)
		return (0);
	ft_export3(export_str, &export, &res);
	if (res != 0)
		return (res);
	if (ft_is_export_in_env(*env, export))
	{
		ft_change_export(env, export);
		return (free(export), 0);
	}
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