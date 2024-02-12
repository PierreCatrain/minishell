/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 00:23:08 by picatrai          #+#    #+#             */
/*   Updated: 2024/02/12 05:01:48 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_parse(t_tree **tree, t_data_parse *data_parse)
{
	t_token	*token;

	token = NULL;
	if (ft_tokenisation(&token, data_parse) != SUCCESS)
		return (ERROR);
	if (ft_condition_grammaire(token) == WRONG_INPUT)
		return (ft_free_token(&token), WRONG_INPUT);
	// ft_print_token(&token);
	if (ft_create_tree(tree, token, data_parse) != SUCCESS)
		return (ft_free_token(&token), ERROR_MALLOC);
	// ft_print_tree(*tree);
	return (GOOD_INPUT);
}
