/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_tree_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 04:09:07 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/03 16:34:33 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**ft_strdup_2d(char **str)
{
	char	**new;
	int		index;

	new = malloc((ft_strlen_2d(str) + 1) * sizeof(char *));
	if (new == NULL)
		return (free_2d(str), NULL);
	index = -1;
	while (str[++index])
	{
		new[index] = ft_strdup(str[index]);
		if (new[index] == NULL)
			return (free_2d(str), ft_free_2d_index(new, index), NULL);
	}
	new[index] = NULL;
	return (new);
}

int	ft_nb_pipes(t_token *token)
{
	int	count;

	count = 0;
	while (token != NULL)
	{
		if (token->type == PIPE)
			count++;
	token = token->next;
	}
	return (count);
}