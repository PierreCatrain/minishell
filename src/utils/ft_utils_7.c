/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_7.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 23:13:46 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/04 17:59:44 by picatrai         ###   ########.fr       */
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

char	*ft_join_char(char *str, char c)
{
	char	*join;
	int			i;

	join = malloc ((ft_strlen(str) + 2) * sizeof(char));
	if (join == NULL)
		return (free(str), NULL);
	i = -1;
	while (str[++i])
		join[i] = str[i];
	join[i++] = c;
	join[i] = '\0';
	return (free(str), join);
}

char	*ft_strjoin(char *str1, char *str2)
{
	char	*join;
	int		i;
	int		j;

	if (str2 == NULL)
		return (str1);
	join = malloc ((ft_strlen(str1) + ft_strlen(str2) + 1) * sizeof(char));
	if (join == NULL)
		return (NULL);
	i = -1;
	while (str1[++i])
		join[i] = str1[i];
	j = -1;
	while (str2[++j])
		join[i + j] = str2[j];
	join[i + j] = '\0';
	return (join);
}

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
