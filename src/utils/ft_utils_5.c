/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:55:49 by lgarfi            #+#    #+#             */
/*   Updated: 2024/02/28 11:03:25 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	count_world(char const *s, char sep)
{
	int	flag;
	int	count;

	if (!s)
		return (0);
	flag = 0;
	count = 0;
	while (*s)
	{
		if (*s != sep && flag == 0)
		{
			count++;
			flag = 1;
		}
		else if (*s == sep)
			flag = 0;
		s++;
	}
	return (count);
}

static char	*dup_word(char const *s, int start, int end)
{
	char	*str;
	int		i;

	str = malloc((end - start) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (start < end)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split(char *s, char c)
{
	char		**tab;
	int			start_word;
	int			j;
	int 		i;

	tab = malloc(sizeof(char *) * (count_world(s, c) + 1));
	if (!tab || !s)
		return (NULL);
	j = 0;
	i = 0;
	start_word = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && start_word < 0)
			start_word = i;
		else if ((s[i] == c || i == ft_strlen(s)) && start_word >= 0)
		{
			tab[j++] = dup_word(s, start_word, i);
			start_word = -1;
		}
		i++;
	}
	tab[j] = 0;
	return (tab);
}

char	*ft_strjoin_path(char *s1, char *s2)
{
	int	i;
	int	j;
	char	*str;

	i = -1;
	str = (char *) malloc (ft_strlen(s1) + ft_strlen(s2) + 2);
	while (s1[++i])
		str[i] = s1[i];
	str[i++] = '/';
	j = -1;
	while (s2[++j])
		str[i + j] = s2[j];
	str[i + j] = '\0';
	free (s1);
	// free (s2);
	return (str);
}

char	*ft_strjoin_path_without_free(char *s1, char *s2)
{
	int	i;
	int	j;
	char	*str;

	i = -1;
	str = (char *) malloc (ft_strlen(s1) + ft_strlen(s2) + 2);
	while (s1[++i])
		str[i] = s1[i];
	str[i++] = '/';
	j = -1;
	while (s2[++j])
		str[i + j] = s2[j];
	str[i + j] = '\0';
	return (str);
}