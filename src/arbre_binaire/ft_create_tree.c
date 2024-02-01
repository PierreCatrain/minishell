/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 02:02:25 by picatrai          #+#    #+#             */
/*   Updated: 2024/01/31 21:35:18 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**ft_strdup_2d(char **str)
{
    char	**new;
    int		index;

	new = malloc((ft_strlen_2d(str) + 1) * sizeof(char *));
	if (new == NULL)
		return (free_2d(str), NULL);
	index = -1;
	while (str[++index])
	{
		new[index] = ft_strdup(str[index]);
		if (new[index] == NULL)
			return (free_2d(str), ft_free_2d_index(new, index), NULL);
	}
	new[index] = NULL;
	return (new);
}

t_lst_exec	*ft_new_lst_exec(char **args, int fd_in, int fd_out)
{
	t_lst_exec	*new;

	new = malloc(sizeof(t_lst_exec));
	if (new == NULL)
		return (NULL);
	new->args = ft_strdup_2d(args);
	if (new->args == NULL)
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	new->fd_in = fd_in;
	new->fd_out = fd_out;
	return (new);
}

t_lst_exec	*ft_lst_exec_last(t_lst_exec *lst_exec)
{
	if (lst_exec == NULL)
		return (NULL);
	while (lst_exec->next != NULL)
		lst_exec = lst_exec->next;
	return (lst_exec);
}

int	ft_lst_exec_add_back(t_lst_exec **lst_exec, t_lst_exec *new)
{
	if (new == NULL)
	{
		return (ERROR_MALLOC);
	}
	if (*lst_exec == NULL)
	{
		*lst_exec = new;
		return (SUCCESS);
	}
	new->prev = ft_lst_exec_last(*lst_exec);
	ft_lst_exec_last(*lst_exec)->next = new;
	return (SUCCESS);
}

int	ft_nb_pipes(t_token *token)
{
	int	count;

	count = 0;
	while (token != NULL)
	{
		if (token->type == PIPE)
			count++;
        token = token->next;
	}
	return (count);
}

void	ft_print_fd_pipe(int **fd_pipes, int nb_pipes)
{
	int	index;

	index = -1;
	printf("\n");
	while (++index < nb_pipes)
	{
		printf("fd pipe n%d/0 -> %d\n", index, fd_pipes[index][0]);
		printf("fd pipe n%d/1 -> %d\n", index, fd_pipes[index][1]);
	}
}

int	ft_lst_exec(t_token *token, t_lst_exec **lst_exec)
{
	char	*heredoc;
	int			fd_in;
	int			fd_out;
	char	**args_tmp;
	int			index_pipes;
	int		**fd_pipes;
	int			nb_pipes;

	//*lst_exec = malloc(sizeof(t_lst_exec));
	nb_pipes = ft_nb_pipes(token);
	fd_pipes = malloc (nb_pipes * sizeof(int *));
	if (fd_pipes == NULL)
		return (ERROR_MALLOC);
	index_pipes = -1;
	while (++index_pipes < nb_pipes)
	{
		fd_pipes[index_pipes] = malloc(2 * sizeof(int));
		if (fd_pipes[index_pipes] == NULL)
			return (ERROR_MALLOC);
		if (pipe(fd_pipes[index_pipes]) == -1)
			return (ERROR_PIPE);
	}
	//ft_print_fd_pipe(fd_pipes, nb_pipes);
	index_pipes = 0;
	fd_in = 0;
	fd_out = 1;
	args_tmp = NULL;
	*lst_exec = NULL;
	while (token != NULL)
	{
		if (token->type == OPEN_PARENTHESIS)
		{
			if (args_tmp != NULL)
			{
				if (ft_lst_exec_add_back(lst_exec, ft_new_lst_exec(args_tmp, fd_in, fd_out)) == ERROR_MALLOC)
					return (ERROR_MALLOC);
				free_2d(args_tmp);
				args_tmp = NULL;
				fd_in = 0;
				fd_out = 1;
			}
		}
		else if (token->type == CLOSE_PARENTHESIS)
		{
			if (args_tmp != NULL)
			{
				if (ft_lst_exec_add_back(lst_exec, ft_new_lst_exec(args_tmp, fd_in, fd_out)) == ERROR_MALLOC)
					return (ERROR_MALLOC);
				free_2d(args_tmp);
				args_tmp = NULL;
				fd_in = 0;
				fd_out = 1;
			}
		}
		else if (token->type == OR)
		{
			if (args_tmp != NULL)
			{
				if (ft_lst_exec_add_back(lst_exec, ft_new_lst_exec(args_tmp, fd_in, fd_out)) == ERROR_MALLOC)
					return (ERROR_MALLOC);
				free_2d(args_tmp);
				args_tmp = NULL;
				fd_in = 0;
				fd_out = 1;
			}
		}
		else if (token->type == AND)
		{
			if (args_tmp != NULL)
			{
				if (ft_lst_exec_add_back(lst_exec, ft_new_lst_exec(args_tmp, fd_in, fd_out)) == ERROR_MALLOC)
					return (ERROR_MALLOC);
				free_2d(args_tmp);
				args_tmp = NULL;
				fd_in = 0;
				fd_out = 1;
			}
		}
		else if (token->type == INFILE)
		{
			if (fd_in != 0 && fd_in != -1)
				close(fd_in);
			token = token->next;
			fd_in = open(token->str, O_RDONLY, 0644);
		}
		else if (token->type == OUTFILE)
		{
			if (fd_out != 1 && fd_out != -1)
				close(fd_out);
			token = token->next;
			fd_out = open(token->str, O_CREAT, O_WRONLY, O_TRUNC, 0644);
		}
		else if (token->type == APPEND)
		{
			if (fd_out != 1 && fd_out != -1)
				close(fd_out);
			token = token->next;
			fd_out = open(token->str, O_CREAT, O_WRONLY, O_APPEND, 0644);
		}
		else if (token->type == HEREDOC)// gerer si on ctrl c ou d depuis le remplissage du here_doc et attention on a open mais pas re close puis re open
		{
			if (fd_in != 0 && fd_in != -1)
				close(fd_in);
			token = token->next;
			heredoc = ft_here_doc();
			if (heredoc == NULL)
				return (ERROR_FILE);
			fd_in = open(heredoc, O_CREAT, O_RDWR, O_TRUNC, 0644);
			ft_complete(fd_in, token);
			unlink(heredoc);
			free(heredoc);
		}
		else if (token->type == PIPE)
		{
			if (fd_out != 1)
				close(fd_pipes[index_pipes][1]);
			else
				fd_out = fd_pipes[index_pipes][1];
			if (ft_lst_exec_add_back(lst_exec, ft_new_lst_exec(args_tmp, fd_in, fd_out)) == ERROR_MALLOC)
				return (ERROR_MALLOC);
			free_2d(args_tmp);
			args_tmp = NULL;
			fd_in = fd_pipes[index_pipes++][0];
			fd_out = 1;
		}
		else
		{
			args_tmp = ft_join_2d(args_tmp, token->str);
			if (args_tmp == NULL)
				return (ERROR_MALLOC);
		}
		if (token->next == NULL)
			break;
		token = token->next;
	}
	if (args_tmp != NULL)
	{
		if (ft_lst_exec_add_back(lst_exec, ft_new_lst_exec(args_tmp, fd_in, fd_out)) == ERROR_MALLOC)
			return (ERROR_MALLOC);
		free_2d(args_tmp);
		args_tmp = NULL;
		fd_in = 0;
		fd_out = 1;
	}
	index_pipes = -1;
	while (++index_pipes < nb_pipes)
		free(fd_pipes[index_pipes]);
	free(fd_pipes);
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

int	ft_create_tree(t_tree **tree, t_token *token)
{
	if (ft_complete_tree(tree, token) != SUCCESS)
		return (ERROR);
	ft_free_token(&token);
	return (SUCCESS);
}
