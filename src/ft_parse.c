/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 00:23:08 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/08 21:18:31 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parse(t_tree **tree, t_data_parse *data_parse, char **env, int exit_status)
{
	t_token	*token;

	token = NULL;
	data_parse->exit_status = exit_status;
	data_parse->env = ft_strdup_2d(env);
	if (data_parse->env == NULL)
		return (ERROR_MALLOC);
	if (ft_tokenisation(&token, data_parse) != SUCCESS)
		return (free_2d(data_parse->env), ERROR);
	if (ft_condition_grammaire(token) == WRONG_INPUT)
		return (free_2d(data_parse->env), ft_free_token(&token), WRONG_INPUT);
	// ft_print_token(&token);
	if (ft_create_tree(tree, token, data_parse) != SUCCESS)
		return (free_2d(data_parse->env), ft_free_token(&token), ERROR_MALLOC);
	// ft_print_tree(*tree);
	return (free_2d(data_parse->env), GOOD_INPUT);
}
