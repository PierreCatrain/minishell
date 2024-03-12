/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 02:23:35 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/12 06:25:26 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_token_type_heredoc(t_data_parse *data_parse, t_token **token)
{
	int	fd_tmp;

	fd_tmp = 0;
	if (data_parse->fd_in == -1 || data_parse->fd_in == -2)
		fd_tmp = data_parse->fd_in;
	else if (data_parse->fd_in > 2)
		close(data_parse->fd_in);
	*token = (*token)->next;
	data_parse->fd_in = \
		data_parse->array_here_doc[data_parse->index_here_doc--];
	if (fd_tmp == -1 || fd_tmp == -2)
	{
		if (data_parse->fd_in > 2)
			close(data_parse->fd_in);
		data_parse->fd_in = fd_tmp;
	}
	return (SUCCESS);
}

int	ft_nb_here_doc(t_token *token)
{
	int	count;

	count = 0;
	while (token != NULL)
	{
		if (token->type == HEREDOC)
			count++;
		token = token->next;
	}
	return (count);
}

int	ft_complete_here_doc(t_data_parse *data_parse, t_token *token, int index)
{
	data_parse->array_here_doc = malloc (ft_nb_here_doc(token) * sizeof(int));
	if (data_parse->array_here_doc == NULL)
		return (ERROR_MALLOC);
	while (token != NULL)
	{
		if (token->type == HEREDOC)
		{
			token = token->next;
			data_parse->heredoc = ft_here_doc();
			if (data_parse->heredoc == NULL)
				return (free(data_parse->array_here_doc), ERROR);
			data_parse->array_here_doc[index] = open(data_parse->heredoc, \
					O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (ft_complete(data_parse->array_here_doc[index], token) == ERROR)
				return (close(data_parse->array_here_doc[index]), free(data_parse->array_here_doc), \
						free(data_parse->heredoc), ERROR);
			close(data_parse->array_here_doc[index]);
			data_parse->array_here_doc[index++] = open(data_parse->heredoc, \
					O_RDWR, 0644);
			unlink(data_parse->heredoc);
			free(data_parse->heredoc);
		}
		token = token->next;
	}
	return (SUCCESS);
}

int	ft_complete(int fd_in, t_token *token)
{
	char	*line;

	if (fd_in == -1)
		return (SUCCESS);
	ft_putstr_fd("> ", 1);
	line = new_readline(token->str);
	if (line == NULL)
	{
		return (ERROR);
	}
	if (ft_strncmp(line, token->str, ft_strlen(token->str)) == 1 \
			|| ft_strlen(token->str) != ft_strlen(line) - 1)
	{
		ft_putstr_fd(line, fd_in);
		free(line);
		if (ft_complete(fd_in, token) == ERROR)
			return (ERROR);
	}
	else
		free(line);
	return (SUCCESS);
}

char	*ft_here_doc(void)
{
	char	*here_doc;
	char	*str;
	char	*str_index;
	int		index;

	str = ft_get_str("/tmp/.here_doc");
	index = 1;
	while (index <= 99999)
	{
		str_index = ft_itoa(index);
		if (str_index == NULL)
			return (ft_print_error_malloc(), NULL);
		here_doc = ft_strjoin(str, str_index);
		if (here_doc == NULL)
			return (free(str_index), ft_print_error_malloc(), NULL);
		free(str_index);
		if (access(here_doc, 0) != 0)
			return (here_doc);
		else
			free(here_doc);
		index++;
	}
	ft_putstr_fd("minishell: heredoc failed\n", 2);
	return (NULL);
}
