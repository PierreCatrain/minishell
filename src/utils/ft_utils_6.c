/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 22:58:50 by picatrai          #+#    #+#             */
/*   Updated: 2024/02/29 18:19:23 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_print_tree(t_tree *tree)
{
	if (tree == NULL)
		return ;
	if (tree->type == EXEC_LIST)
	{
		ft_print_lst_exec(tree->lst_exec);
	}
	else if (tree->type == OPPERATOR_AND)
	{
		printf("AND\n");
	}
	else if (tree->type == OPPERATOR_OR)
	{
		printf("OR\n");
	}
	if (tree->left_child != NULL)
	{
		printf("left child\n");
		ft_print_tree(tree->left_child);
	}
	if (tree->right_child != NULL)
	{
		printf("right child\n");
		ft_print_tree(tree->right_child);
	}
	return ;
}

char	*ft_get_str(char *str)
{
	return (str);
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
int	ft_is_ascii(char c)
{
	return (!(c >= '0' && c <= '9'));
}
