/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 03:45:01 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/18 01:31:16 by picatrai         ###   ########.fr       */
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
        printf("str %s, type %d\n", (*token)->str, (*token)->type);
        *token = (*token)->next;
    }
    printf("str %s, type %d\n", (*token)->str, (*token)->type);
    while ((*token)->prev != NULL)
        *token = (*token)->prev;
}

int	ft_isalphanum(int c)
{
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_')
    {
        return (1);
    }
    return (0);
}

int ft_strcmp(char *str1, char *str2)
{
    int index;

    index = 0;
    while (str1[index] && str2[index] && (str1[index] == str2[index]))
	{
        index++;
	}
    return (str1[index] - str2[index]);
}

int	ft_count_itoa(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		count++;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*itoa;
	int		len;
	long	long_n;

	len = ft_count_itoa(n);
	long_n = n;
	itoa = (char *)malloc((len + 1) * sizeof(char));
	if (itoa == NULL)
		return (NULL);
	itoa[len] = '\0';
	if (long_n < 0)
		long_n *= -1;
	while (len > 0)
	{
		itoa[len - 1] = (long_n % 10) + '0';
		long_n /= 10;
		len--;
	}
	if (n < 0)
	itoa[0] = '-';
	return (itoa);
}