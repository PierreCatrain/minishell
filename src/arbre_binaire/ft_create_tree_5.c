/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_tree_5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 04:13:45 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/03 13:58:11 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_exec_token_type_2(t_data_parse *data_parse, t_token *token)
{
	char *str_tmp;
	
	if (token->type == INFILE)
	{
		if (data_parse->fd_in != 0 && data_parse->fd_in != -1)
			close(data_parse->fd_in);
		token = token->next;
		str_tmp = transfo_expand(token->str, token->expand);
		if (str_tmp == NULL)
			return (ERROR);
		data_parse->fd_in = open(str_tmp, O_RDONLY);
		free(str_tmp);
	}
	else if (token->type == OUTFILE)
	{
		if (data_parse->fd_out != 1 && data_parse->fd_out != -1)
			close(data_parse->fd_out);
		token = token->next;
		str_tmp = transfo_expand(token->str, token->expand);
		if (str_tmp == NULL)
			return (ERROR);
		data_parse->fd_out = open(str_tmp, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		free(str_tmp);
	}
	else if (token->type == APPEND)
	{
		if (data_parse->fd_out != 1 && data_parse->fd_out != -1)
			close(data_parse->fd_out);
		token = token->next;
		str_tmp = transfo_expand(token->str, token->expand);
		if (str_tmp == NULL)
			return (ERROR);
		data_parse->fd_out = open(str_tmp, O_CREAT | O_WRONLY | O_APPEND, 0644);
		free(str_tmp);
	}
	return (SUCCESS);
}

int	ft_exec_token_type_heredoc(t_data_parse *data_parse, t_token **token)
{
	if (data_parse->fd_in != 0 && data_parse->fd_in != -1)
		close(data_parse->fd_in);
	*token = (*token)->next;
	data_parse->fd_in = data_parse->array_here_doc[data_parse->index_here_doc--];
	return (SUCCESS);
}

int	ft_exec_token_type_pipe(t_data_parse *data_parse, t_lst_exec **lst_exec)
{
	if (data_parse->fd_out != 1)
		close(data_parse->fd_pipes[data_parse->index_pipes][1]);
	else
		data_parse->fd_out = data_parse->fd_pipes[data_parse->index_pipes][1];
	if (ft_lst_exec_add_back(lst_exec, ft_new_lst_exec(data_parse->args_tmp, \
					data_parse->fd_in, data_parse->fd_out, data_parse->expand)) == ERROR_MALLOC)
		return (ft_free_pipes(data_parse->fd_pipes, data_parse->nb_pipes), \
				free_2d(data_parse->args_tmp), \
				ft_print_error_malloc(), ERROR_MALLOC);
	free_2d(data_parse->args_tmp);
	data_parse->args_tmp = NULL;
	data_parse->expand = NULL;//
	data_parse->fd_in = data_parse->fd_pipes[data_parse->index_pipes++][0];
	data_parse->fd_out = 1;
	return (SUCCESS);
}

int	ft_is_token_type_1(t_token *token)
{
	if (token->type == OPEN_PARENTHESIS || token->type == CLOSE_PARENTHESIS \
	|| token->type == OR || token->type == AND)
		return (SUCCESS);
	return (ERROR);
}

int	ft_is_token_type_2(t_token *token)
{
	if (token->type == INFILE || token->type == OUTFILE \
	|| token->type == APPEND)
		return (SUCCESS);
	return (ERROR);
}
