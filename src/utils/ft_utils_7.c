/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_7.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 23:13:46 by picatrai          #+#    #+#             */
/*   Updated: 2024/02/12 04:54:14 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

char *ft_str_cat_long_long(char *new_str, long long g_exit_status)
{
	char *exit;
	char *cat;
	int i;
	int j;
	
	exit = ft_itoa_long_long(g_exit_status);
	if (exit == NULL)
		return (free(new_str), NULL);
	cat = malloc ((ft_strlen(new_str) + ft_strlen(exit) + 1) * sizeof(char));
	if (cat == NULL)
		return (free(exit), free(new_str), NULL);
	i = -1;
	while (new_str[++i])
		cat[i] = new_str[i];
	j = -1;
	while (exit[++j])
		cat[i + j] = exit[j];
	cat[i + j] = '\0';
	return (free(exit), free(new_str), cat);
}

char *ft_str_cat_char(char *new_str, char c)
{
	char *cat;
	int index;
	
	cat = malloc((ft_strlen(new_str) + 2) * sizeof(char));
	if (cat == NULL)
		return (free(new_str), NULL);
	index = -1;
	while (new_str[++index])
	{
		cat[index] = new_str[index];
	}
	cat[index++] = c;
	cat[index] = '\0';
	return (free(new_str), cat);
}

char *ft_replace_exit_status(char *str)
{
	char *new_str;
	int index;

	new_str = malloc (sizeof(char));
	if (new_str == NULL)
		return (NULL);
	new_str[0] = '\0';
	index = 0;
	while (str[index])
	{
		if (str[index] == '$' && str[index + 1] == '?')
		{
			index++;
			new_str = ft_str_cat_long_long(new_str, g_exit_status);
			if (new_str == NULL)
				return (NULL);
		}
		else
		{
			new_str = ft_str_cat_char(new_str, str[index]);
			if (new_str == NULL)
				return (NULL);
		}
		index++;
	}
	return (new_str);
}

void ft_free_index_new_args(char **str, int index)
{
	index--;
	while (index >= 0)
		free(str[index]);
	free(str);
}

char **new_args(char **args)
{
	char **new_args;
	int index;
	
	new_args = malloc ((ft_strlen_2d(args) + 1) * sizeof(char *));
	if (new_args == NULL)
		return (NULL);
	index = -1;
	while (args[++index])
	{
		new_args[index] = ft_replace_exit_status(args[index]);
		if (new_args[index] == NULL)
			return (ft_free_index_new_args(new_args, index), NULL);
	}
	new_args[index] = NULL;
	return (new_args);
}

// int	main(int ac, char **av)
// {
// 	char **args;

// 	(void)ac;
// 	args = new_args(av + 1);
// 	print_tab_tab(args);
// 	return (0);
// }