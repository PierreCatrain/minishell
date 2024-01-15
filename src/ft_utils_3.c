/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 03:45:01 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/15 01:58:02 by picatrai         ###   ########.fr       */
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
    if (*token == NULL)
        return ;
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

int	ft_isalphanum(int c)
{
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_')
    {
        return (1);
    }
    return (0);
}