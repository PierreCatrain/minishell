/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 02:02:25 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/04 12:15:54 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_interpret_token(t_data_parse *data_parse, \
		t_lst_exec **lst_exec, t_token **token)
{
	if (ft_is_token_type_1(*token) == SUCCESS)
	{
		if (ft_exec_token_type_1(data_parse, lst_exec, *token) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	else if (ft_is_token_type_2(*token) == SUCCESS)
	{
		if (ft_exec_token_type_2(data_parse, *token) != SUCCESS)
			return (ERROR);
		*token = (*token)->next;//
	}
	else if ((*token)->type == HEREDOC)
	{
		if (ft_exec_token_type_heredoc(data_parse, token) != SUCCESS)
			return (ERROR);
	}
	else if ((*token)->type == PIPE)
	{
		if (ft_exec_token_type_pipe(data_parse, lst_exec) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	else
	{
		data_parse->args_tmp = ft_join_2d(data_parse->args_tmp, (*token)->str);
		if (data_parse->args_tmp == NULL)
			return (ft_free_pipes(data_parse->fd_pipes, data_parse->nb_pipes), \
			ft_print_error_malloc(), ERROR_MALLOC);
		if (ft_complete_expand(&data_parse->expand, (*token)->expand, ft_strlen_2d(data_parse->args_tmp)) == ERROR_MALLOC)//
			return (ERROR_MALLOC);//
	}
	return (SUCCESS);
}

int	ft_lst_exec(t_token *token, t_lst_exec **lst_exec, t_data_parse *data_parse)
{
	if (ft_set_exec(data_parse, lst_exec, token) != SUCCESS)
		return (ERROR);
	while (token != NULL)
	{
		if (ft_interpret_token(data_parse, lst_exec, &token) != SUCCESS)
		{
			while (++data_parse->index_pipes < data_parse->nb_pipes)
				free(data_parse->fd_pipes[data_parse->index_pipes]);
			free(data_parse->fd_pipes);
			return (ERROR);
		}
		if (token->next == NULL)
			break ;
		token = token->next;
	}
	if (ft_one_more_exec(data_parse, lst_exec) == ERROR_MALLOC)
		return (ERROR_MALLOC);
	data_parse->index_pipes = -1;
	while (++data_parse->index_pipes < data_parse->nb_pipes)
		free(data_parse->fd_pipes[data_parse->index_pipes]);
	free(data_parse->fd_pipes);
	return (SUCCESS);
}

int	ft_nb_lst_exec(t_token *token)
{
	int	count;

	count = 1;
	while (token != NULL)
	{
		if (token->type == AND || token->type == OR)
			count++;
		token = token->next;
	}
	return (count);
}

int	ft_create_tree(t_tree **tree, t_token *token, t_data_parse *data_parse)
{	
	if (ft_complete_here_doc(data_parse, token) != SUCCESS)
		return (ERROR);
	if (ft_complete_tree(tree, token, data_parse) != SUCCESS)
		return (free(data_parse->array_here_doc), free_and_close_tree(*tree), ERROR);
	ft_free_token(&token);
	free(data_parse->array_here_doc);
	return (SUCCESS);
}
