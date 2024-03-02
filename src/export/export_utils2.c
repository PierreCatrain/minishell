/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 19:41:27 by lgarfi            #+#    #+#             */
/*   Updated: 2024/02/29 19:41:39 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_env_value(char ***new_env)
{
	int	i;

	i = -1;
	while ((*new_env)[++i])
	{
		if (value_start_equal((*new_env)[i]) == 1)
		{
			(*new_env)[i] = add_quote_to_value((*new_env)[i]);
		}
	}
}
