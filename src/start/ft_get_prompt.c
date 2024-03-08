/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 21:50:13 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/04 18:09:17 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_at_home(char *start_prompt, char *end_prompt, char *str)
{
	char	*prompt;
	int		i;
	int		j;

	prompt = malloc ((ft_strlen(start_prompt) \
	+ ft_strlen(end_prompt) + 6) * sizeof(char));
	if (prompt == NULL)
		return (ft_print_error_malloc(), NULL);
	i = -1;
	while (start_prompt[++i])
		prompt[i] = start_prompt[i];
	j = -1;
	while (++j < ft_strlen(str))
		prompt[i + j] = str[j];
	i += j;
	j = -1;
	while (end_prompt[++j])
		prompt[i + j] = end_prompt[j];
	prompt[i + j] = '\0';
	return (prompt);
}

char	*ft_at_user(char *start_prompt, char *end_prompt)
{
	char	*prompt;
	int		i;
	int		j;

	prompt = malloc ((ft_strlen(start_prompt) \
	+ ft_strlen(end_prompt) + 2) * sizeof(char));
	if (prompt == NULL)
		return (ft_print_error_malloc(), NULL);
	i = -1;
	while (start_prompt[++i])
		prompt[i] = start_prompt[i];
	prompt[i++] = '~';
	j = -1;
	while (end_prompt[++j])
		prompt[i + j] = end_prompt[j];
	prompt[i + j] = '\0';
	return (prompt);
}

char	*ft_at_else(char *start_prompt, char *end_prompt, char *str)
{
	char	*prompt;
	int		i[2];

	i[0] = -1;
	i[1] = 0;
	while (str[++i[0]] && i[1] < 3)
	{
		if (str[i[0]] == '/')
			i[1]++;
	}
	prompt = malloc ((ft_strlen(start_prompt) + ft_strlen(end_prompt) \
	+ ft_strlen(str) - i[0]-- + 3) * sizeof(char));
	if (prompt == NULL)
		return (ft_print_error_malloc(), NULL);
	i[1] = -1;
	while (start_prompt[++i[1]])
		prompt[i[1]] = start_prompt[i[1]];
	prompt[i[1]++] = '~';
	while (str[i[0]])
		prompt[i[1]++] = str[i[0]++];
	i[0] = -1;
	while (end_prompt[++i[0]])
		prompt[i[1] + i[0]] = end_prompt[i[0]];
	prompt[i[1] + i[0]] = '\0';
	return (prompt);
}

char	*ft_get_prompt(void)
{
	char	*prompt;
	char	*start_prompt;
	char	*end_prompt;
	char	wd[WD_BUFFER_SIZE];

	start_prompt = ft_get_str("\1\033[1;33m\2minishell \1\033[1;34m\2WD:(\1\033[1;31m\2");
	end_prompt = ft_get_str("\1\033[1;34m\2)\1\033[1;33m\2 ~ \1\033[0m\2");
	if (getcwd(wd, WD_BUFFER_SIZE) == NULL)
		return (NULL);
	if (ft_occ(wd, '/') == 1)
	{
		prompt = ft_at_home(start_prompt, end_prompt, wd);
		return (prompt);
	}
	else if (ft_occ(wd, '/') == 2 && ft_strncmp(wd, "/home/", 6) == 0)
	{
		prompt = ft_at_user(start_prompt, end_prompt);
		return (prompt);
	}
	prompt = ft_at_else(start_prompt, end_prompt, wd);
	return (prompt);
}
