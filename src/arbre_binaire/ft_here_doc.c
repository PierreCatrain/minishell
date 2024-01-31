/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 02:23:35 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/30 21:35:23 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char *ft_strjoin(char *str1, char *str2)
{
    char *join;
    int i;
    int j;

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

int is_pipe_in_suite_exec(t_token *token)
{
	while (token != NULL)
	{
		if (token->type == AND || token->type == OR || token->type == CLOSE_PARENTHESIS)// normalement pas possible qu'il y ai (
			return (0);
		if (token->type == PIPE)
			return (PIPE);
		token = token->next;
	}
	return (0);
}

void	ft_complete(int fd_in, t_token *token)
{
	char *str;
	char	*line;

	if (is_pipe_in_suite_exec(token) == PIPE)
		str = ft_get_str("pipe heredoc>");
	else
		str = ft_get_str("heredoc>");
	line = readline(str);
	if (ft_strcmp(line, token->str) != 0)
	{
		ft_putstr_fd(line, fd_in);
		free(line);
		ft_complete(fd_in, token);
	}
	else
		free(line);
}

char *ft_here_doc(void)
{
	char *here_doc;
    char *str;
	char *str_index;
	int index;
	
	str = ft_get_str(".here_doc");
	index = 1;
	while (index <= 99999)
	{
		str_index = ft_itoa(index);
		if (str_index == NULL)
			return (NULL);
		here_doc = ft_strjoin(str, str_index);
		if (here_doc == NULL)
			return (free(str_index), NULL);
		free(str_index);
		if (access(here_doc, 0) != 0)
			return (here_doc);
		else
			free(here_doc);
		index++;
	}
    return (NULL);
}