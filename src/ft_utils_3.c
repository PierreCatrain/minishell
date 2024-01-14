/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 03:45:01 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/14 04:07:15 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_lstsize(t_token *token)
{
	int	count;

	count = 0;
	while (token != NULL)
	{
		token = token->next;
		count++;
	}
	return (count);
}

void    ft_print_token(t_token **token)
{
    printf("size %d\n\n", ft_lstsize(*token));
    while ((*token)->next != NULL)
    {
        printf("croissant %s\n", (*token)->str);
        *token = (*token)->next;
    }
    printf("croissant %s\n\n", (*token)->str);
    while ((*token)->prev != NULL)
    {
        printf("decroissant %s\n", (*token)->str);
        *token = (*token)->prev;
    }
    printf("decroissant %s\n", (*token)->str);
}