/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_tree_4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 04:11:28 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/04 11:56:50 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_free_pipes(int **fd_pipes, int nb_pipes)
{
	while (--nb_pipes >= 0)
	{
		free(fd_pipes[nb_pipes]);
	}
	free(fd_pipes);
}

void	ft_pipes_fail(int **fd_pipes, int index_pipes)
{
	index_pipes--;
	while (index_pipes >= 0)
	{
		close(fd_pipes[index_pipes][0]);
		close(fd_pipes[index_pipes][1]);
		free(fd_pipes[index_pipes]);
		index_pipes--;
	}
	free(fd_pipes);
}

int	ft_one_more_exec(t_data_parse *data_parse, t_lst_exec **lst_exec)
{
	if (data_parse->args_tmp != NULL)
	{
		if (ft_lst_exec_add_back(lst_exec, \
		ft_new_lst_exec(data_parse->args_tmp, \
		data_parse->fd_in, data_parse->fd_out, data_parse->expand)) == ERROR_MALLOC)
			return (ft_free_pipes(data_parse->fd_pipes, data_parse->nb_pipes), \
			free_2d(data_parse->args_tmp), ft_print_error_malloc(), \
			ERROR_MALLOC);
		free_2d(data_parse->args_tmp);
		data_parse->expand = NULL;//
		data_parse->args_tmp = NULL;
		data_parse->fd_in = 0;
		data_parse->fd_out = 1;
	}
	return (SUCCESS);
}

int	ft_set_exec(t_data_parse *data_parse, t_lst_exec **lst_exec, t_token *token)
{
	data_parse->nb_pipes = ft_nb_pipes(token);
	data_parse->fd_pipes = malloc (data_parse->nb_pipes * sizeof(int *));
	if (data_parse->fd_pipes == NULL)
		return (ft_print_error_malloc(), ERROR_MALLOC);
	data_parse->index_pipes = -1;
	while (++data_parse->index_pipes < data_parse->nb_pipes)
	{
		data_parse->fd_pipes[data_parse->index_pipes] = malloc(2 * sizeof(int));
		if (data_parse->fd_pipes[data_parse->index_pipes] == NULL)
			return (ft_pipes_fail(data_parse->fd_pipes, \
			data_parse->index_pipes), \
			ft_print_error_malloc(), ERROR_MALLOC);
		if (pipe(data_parse->fd_pipes[data_parse->index_pipes]) == -1)
			return (free(data_parse->fd_pipes[data_parse->index_pipes]), \
			ft_pipes_fail(data_parse->fd_pipes, data_parse->index_pipes), \
			ft_putstr_fd("minishell: pipes failed\n", 2), ERROR_PIPE);
	}
	data_parse->index_pipes = 0;
	data_parse->fd_in = 0;
	data_parse->fd_out = 1;
	data_parse->args_tmp = NULL;
	data_parse->expand = NULL;//
	*lst_exec = NULL;
	return (SUCCESS);
}

int	ft_exec_token_type_1(t_data_parse *data_parse, \
		t_lst_exec **lst_exec, t_token *token)
{
	if (token->type == OPEN_PARENTHESIS)
	{
		if (ft_one_more_exec(data_parse, lst_exec) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	else if (token->type == CLOSE_PARENTHESIS)
	{
		if (ft_one_more_exec(data_parse, lst_exec) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	else if (token->type == OR)
	{
		if (ft_one_more_exec(data_parse, lst_exec) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	else if (token->type == AND)
	{
		if (ft_one_more_exec(data_parse, lst_exec) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	return (SUCCESS);
}
