/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 06:51:13 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/05 11:11:36 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_expand_step_1(t_lst_exec *lst_exec, int status, char **env)
{
	char	**new_args;
	int		index;

	new_args = malloc ((ft_strlen_2d(lst_exec->args) + 1) * sizeof(char *));
	if (new_args == NULL)
		return (NULL);
	index = 0;
	while (index < lst_exec->len_expand)
	{
		new_args[index] = ft_replace_env_variable(lst_exec->args[index], \
				lst_exec->expand[index], env, status);
		if (new_args[index] == NULL)
			return (NULL);
		index++;
	}
	new_args[index] = NULL;
	return (new_args);
}

char	**ft_expand_step_2(t_lst_exec *lst_exec, char **args, t_wildcard *ls)
{
	char	**new_args;
	int		index;

	new_args = NULL;
	index = 0;
	while (index < lst_exec->len_expand)
	{
		new_args = ft_add_wildcard(new_args, args[index], ls, 0);
		if (new_args == NULL)
			return (free(args), NULL);
		index++;
	}
	free(args);
	return (new_args);
}

char	**ft_new_args(t_lst_exec *lst_exec, int status, char **env)
{
	t_wildcard	*ls;
	char		**new_args;

	ls = NULL;
	lst_exec->len_expand = ft_strlen_2d(lst_exec->args);
	new_args = ft_expand_step_1(lst_exec, status, env);
	if (new_args == NULL)
		return (NULL);
	if (set_ls(&ls) != SUCCESS)
		return (NULL);
	new_args = ft_expand_step_2(lst_exec, new_args, ls);
	if (new_args == NULL)
		return (ft_free_wildcard(&ls), NULL);
	return (ft_free_wildcard(&ls), new_args);
}
