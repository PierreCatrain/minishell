/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_7.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 23:13:46 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/02 07:37:38 by picatrai         ###   ########.fr       */
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
