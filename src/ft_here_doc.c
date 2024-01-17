/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 02:23:35 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/16 02:54:23 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char *ft_strjoin_only_second(char *str1, char *str2)
{
    char *join;
    int i;
    int j;
    
    if (str2 == NULL)
        return (str1);
    join = malloc ((ft_strlen(str2) + 1) * sizeof(char));
    if (join == NULL)
        return (free(str1), NULL);
    i = -1;
    while (str1[++i])
        join[i] = str1[i];
    j = -1;
    while (str2[++j])
        join[i + j] = str2[j];
    join[i + j] = '\0';
    return (free(str2), join);
}

int	ft_get_str_here(char *str, char **new_str)
{
    char *str_index;
	int	index;

	index = 1;
	while (index <= 99999)
	{
		str_index = ft_itoa(index);
		if (str_index == NULL)
			return (0);
		new_str = ft_strjoin(str, str_index);
		if (new_str == NULL)
			return (free(str_index), 0);
		if (access(new_str, 0) != 0)
			return (1);
		else
			free(new_str);
		index++;
	}
	return (0);
}

void	ft_complete(t_token *token, int fd)
{
	char	*line;

	line = readline("here_doc>");
	if (ft_strcmp(line, token->next->str) != 0)
	{
		ft_putstr_fd(line, fd);
		free(line);
		ft_complete(token, fd);
	}
	else
		free(line);
}

t_token *ft_here_doc(t_token *token)
{
    char *str;
    int fd;

    if (ft_get_str_here(".here_doc", &str) == 0)
        return (free(str), NULL);
    fd = open(str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (ft_putstr_fd("error with here_doc\n", 2), free(str), NULL);
    ft_complete(token, fd);
    close(fd);
	fd = open(str, O_RDONLY, 0644);
	if (fd < 0)
	{
		unlink(str);
		free(str);
		return (ft_putstr_fd("error with here_doc\n", 2), free(str), NULL);
	}
	unlink(str);
    free(str);
    return ();
}