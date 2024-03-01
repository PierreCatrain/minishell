/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:54:03 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/01 14:24:56 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_str_join_export_name_with_equal_value(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*new_export;

	i = -1;
	new_export = (char *) malloc (ft_strlen(s1) + ft_strlen(s2) + 1);
	while (s1[++i])
		new_export[i] = s1[i];
	j = -1;
	while (s2[++j])
		new_export[i++] = s2[j];
	new_export[i] = '\0';
	free(s1);
	free(s2);
	return (new_export);
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

char	*ft_strjoin_wihtout_free(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	str = (char *) malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = -1;
	while (s2[++j])
		str[i + j] = s2[j];
	str[i + j] = '\0';
	return (str);
	
}

char	*ft_strjoin_one_malloc(char *new_str, char *str_tmp)
{
	char	*join;
	int			i;
	int			j;

	if (str_tmp == NULL)
		return (new_str);
	join = malloc ((ft_strlen(new_str) + ft_strlen(str_tmp) + 1) * sizeof(char));
	if (join == NULL)
		return (free(new_str), NULL);
	i = -1;
	while (new_str[++i])
		join[i] = new_str[i];
	j = -1;
	while (str_tmp[++j])
		join[i + j] = str_tmp[j];
	join[i + j] = '\0';
	return (free(new_str), join);
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
