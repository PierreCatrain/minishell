/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 06:51:13 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/10 19:55:27 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_new_args(t_lst_exec *lst_exec, int status, char **env)
{
	char			**new_args;
	int				index;
	t_data_expand	data_expand;

	data_expand.env = env;
	data_expand.status = status;
	lst_exec->len_expand = ft_strlen_2d(lst_exec->args);
	new_args = malloc (sizeof(char *));
	if (new_args == NULL)
		return (NULL);
	new_args[0] = NULL;
	index = 0;
	while (index < lst_exec->len_expand)
	{
		new_args = ft_add_and_replace_env_variable(lst_exec->args[index], \
				lst_exec->expand[index], &data_expand, new_args);
		if (new_args == NULL)
			return (NULL);
		index++;
	}
	return (new_args);
}
