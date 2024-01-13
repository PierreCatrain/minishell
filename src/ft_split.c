/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 00:50:23 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/13 00:50:47 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_free_split(char **split, int j)
{
	j--;
	while (j >= 0)
		free(split[j--]);
	free(split);
}

int	ft_mega_malloc(char *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != '\0' && str[i] != c && (str[i + 1] == '\0' \
					|| str[i + 1] == c))
			count++;
		i++;
	}
	return (count);
}

int	ft_mini_malloc(char *str, char c, int i)
{
	int	count;

	count = 0;
	while (str[i] != '\0' && str[i] != c)
	{
		i++;
		count++;
	}
	return (count);
}

char	*ft_remplissage_split(char *str, char c, int i)
{
	char	*mini_split;
	int		j;

	mini_split = malloc((ft_mini_malloc(str, c, i) + 1) * sizeof(char));
	if (mini_split == NULL)
		return (NULL);
	j = 0;
	while (str[i + j] != '\0' && str[i + j] != c)
	{
		mini_split[j] = str[i + j];
		j++;
	}
	mini_split[j] = '\0';
	return (mini_split);
}

char	**ft_split(char *str, char c)
{
	char	**split;
	int		i;
	int		j;
	int		new;

	split = malloc((ft_mega_malloc(str, c) + 1) * sizeof(char *));
	if (split == NULL)
		return (NULL);
	i = -1;
	j = -1;
	new = 1;
	while (str[++i])
	{
		if (new == 1 && str[i] != c)
		{
			split[++j] = ft_remplissage_split(str, c, i);
			if (split[j] == NULL)
				return (ft_free_split(split, j), NULL);
			new = 0;
		}
		else if (new == 0 && str[i] == c && str[i + 1] != c \
		&& str[i + 1] != '\0')
			new = 1;
	}
	return (split[++j] = 0, split);
}