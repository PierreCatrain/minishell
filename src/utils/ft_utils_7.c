/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_7.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 23:13:46 by picatrai          #+#    #+#             */
/*   Updated: 2024/02/29 19:51:07 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_invalid_token(char *str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("'\n", 2);
}

char	*ft_strdup(char *str)
{
	char	*new;
	int		index;

	new = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (new == NULL)
		return (NULL);
	index = -1;
	while (str[++index])
		new[index] = str[index];
	new[index] = '\0';
	return (new);
}

void	ft_print_fd_pipe(int **fd_pipes, int nb_pipes)
{
	int	index;

	index = -1;
	printf("\n");
	printf("nb pipes = %d\n", nb_pipes);
	while (++index < nb_pipes)
	{
		printf("fd pipe n%d/0 -> %d\n", index, fd_pipes[index][0]);
		printf("fd pipe n%d/1 -> %d\n", index, fd_pipes[index][1]);
	}
}

int ft_size_malloc_long_long(long long nb)
{
	int count;

	count = 0;
	if (nb >= 0 && nb <= 9)
		return (1);
	if (nb < 0)
	{
		nb *= -1;
		count++;
	}
	while (nb > 0)
	{
		count++;
		nb /= 10;
	}
	return (count);
}

char *ft_itoa_long_long(long long nb)
{
	char *str;
	int count;
	int index;
	
	count = ft_size_malloc_long_long(nb);
	str = malloc ((count + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	index = count - 1;
	while (index >= 0)
	{
		str[index--] = (nb % 10) + 48;
		nb /= 10;
	}
	str[count] = '\0';
	return (str);	
}

// int	main(int ac, char **av)
// {
// 	char **args;

// 	(void)ac;
// 	args = new_args(av + 1);
// 	print_tab_tab(args);
// 	return (0);
// }