/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 03:45:01 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/01 05:40:31 by picatrai         ###   ########.fr       */
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

void	ft_print_token(t_token **token)
{
	if (*token == NULL)
	{
		return ;
	}
	while ((*token)->prev != NULL)
		*token = (*token)->prev;
	printf("size %d\n\n", ft_lstsize(*token));
	while ((*token)->next != NULL)
	{
		printf("%s ", (*token)->str);
		ft_print_expand((*token)->expand);
		printf("\n");
		*token = (*token)->next;
	}
	printf("%s ", (*token)->str);
	ft_print_expand((*token)->expand);
	printf("\n");
	while ((*token)->prev != NULL)
		*token = (*token)->prev;
}

int	ft_isalphanum(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') \
			|| (c >= '0' && c <= '9') || c == '_')
	{
		return (1);
	}
	return (0);
}

int	ft_strcmp(char *str1, char *str2)
{
	int	index;

	index = 0;
	while (str1[index] && str2[index] && (str1[index] == str2[index]))
		index++;
	return (str1[index] - str2[index]);
}

void ft_print_expand(t_expand *expand)
{
	int index;

	index = 0;
	printf(" expand ");
	while (expand != NULL)
	{
		printf("/ %d ", expand->action);
		expand = expand->next;
	}
	printf(" || ");
}

void	ft_printf_2d(char **str, t_expand **expand)
{
	int	index;

	printf("args-> ");
	index = 0;
	while (str[index])
	{
		printf("%s ", str[index]);
		if (expand != NULL)
			ft_print_expand(expand[index]);
		index++;
	}
	printf("\n");
}
