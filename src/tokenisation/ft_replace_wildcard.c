/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_wildcard.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:41:55 by picatrai          #+#    #+#             */
/*   Updated: 2024/02/01 02:28:09 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_strjoin_1_malloc(char *str1, char *str2)
{
	char	*join;
	int			i;
	int			j;

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
	return (free(str1), join);
}

void	ft_print_2d(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		printf("\tstr %s\n", str[i]);
}

t_wildcard	*ft_lst_wildcard_new(char *str)
{
	t_wildcard	*new;

	new = malloc(sizeof(t_wildcard));
	if (new == NULL)
		return (NULL);
	new->prev = NULL;
	new->next = NULL;
	new->str = ft_strdup(str);
	if (new->str == NULL)
		return (free(new), NULL);
	return (new);
}

t_wildcard	*ft_lst_wildcard_last(t_wildcard *ls)
{
	while (ls->next != NULL)
		ls = ls->next;
	return (ls);
}

int	ft_lst_wildcard_add_back(t_wildcard **ls, t_wildcard *new)
{
	if (new == NULL)
		return (ERROR_MALLOC);
	if (*ls == NULL)
	{
		*ls = new;
		return (SUCCESS);
	}
	new->prev = ft_lst_wildcard_last(*ls);
	ft_lst_wildcard_last(*ls)->next = new;
	return (SUCCESS);
}

int	set_ls(t_wildcard **ls)
{
	DIR	*directory;
	struct	dirent *entry;

	directory = opendir(".");
	if (directory == NULL)
	{
		printf("minishell: opendir failed\n");
		return (ERROR);
	}
	while (1)
	{
		entry = readdir(directory);
		if (entry == NULL)
			break ;
		if (ft_lst_wildcard_add_back(ls, ft_lst_wildcard_new(entry->d_name)) != SUCCESS)
		{
			closedir(directory);
			return (ft_print_error_malloc(), ERROR_MALLOC);
		}
	}
	closedir(directory);
	return (SUCCESS);
}

void	ft_free_wildcard(t_wildcard **ls)
{
	t_wildcard	*tmp;

	while ((*ls)->prev != NULL)
		*ls = (*ls)->prev;
	while (*ls != NULL)
	{
		tmp = *ls;
		*ls = (*ls)->next;
		free(tmp->str);
		free(tmp);
	}
}

int	ft_strlen_before(char *str)
{
	int	index;

	index = 0;
	while (str[index] && str[index] != '*')
		index++;
	return (index);
}

int	ft_strlen_after(char *str)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	while (str[index] && str[index] != '*')
		index++;
	if (str[index] == '*')
		index++;
	while (str[index++])
		count++;
	return (count);
}

char	*ft_only_end_str(char *str, int size)
{
	int	index;

	index = 0;
	while (str[index])
		index++;
	if (index < size)
		return (NULL);
	return (&str[index - size]);
}

int	match_with_wildcard(char *before, char *after, char *str)
{
	int	good;

	if ((ft_strlen(before) + ft_strlen(after)) > ft_strlen(str))
		return (ERROR);
	good = 0;
	if ((before == NULL && str[0] != '.') || ft_strncmp(before, str, ft_strlen(before)) == 0)
		good++;
	if (after == NULL || ft_strncmp(after, ft_only_end_str(str, ft_strlen(after)), ft_strlen(after)) == 0)
		good++;
	if (good != 2)
		return (ERROR);
	return (SUCCESS);
}

int	ft_wildcard_before_and_after(t_token **token, t_wildcard *ls, int *find)
{
	char	*before;
	char	*after;
	int	index;
	int	i;
	int	part;

	index = -1;
	i = 0;
	part = 1;
	before = malloc((ft_strlen_before((*token)->str) + 1) * sizeof(char));
	if (before == NULL)
		return (ERROR_MALLOC);
	before[0] = '\0';
	after = malloc((ft_strlen_after((*token)->str) + 1) * sizeof(char));
	if (after == NULL)
		return (free(before), ERROR_MALLOC);
	after[0] = '\0';
	while ((*token)->str[++index])
	{
		if ((*token)->str[index] == '*')
		{
			before[i] = '\0';
			part = 2;
			i = 0;
		}
		else
		{
			if (part == 1)
				before[i++] = (*token)->str[index];
			else if (part == 2)
				after[i++] = (*token)->str[index];
		}
	}
	if (part == 2)
		after[i] = '\0';
	while (ls != NULL)
	{
		if (match_with_wildcard(before, after, ls->str) == SUCCESS)
		{
			if (ft_lst_insert(token, ft_lstnew_no_malloc(ls->str, WORD, TEXT)) == ERROR_MALLOC)
				return (free(before), free(after), ERROR_MALLOC);
			*find = 1;
		}
		if (ls->prev == NULL)
			break ;
		ls = ls->prev;
	}
	free(before);
	free(after);    
	return (SUCCESS);
}

int	ft_insert_wildcard(t_token **token)
{
	int	find;
	t_wildcard	*ls;

	find = 0;
	ls = NULL;
	if (set_ls(&ls) != SUCCESS)
		return (ERROR);
	if (ls == NULL)
		return (SUCCESS);
	while (ls->next != NULL)
		ls = ls->next;
	if (ft_strlen((*token)->str) == 1)
	{
		while (ls != NULL)
		{
			if (ls->str[0] != '.')
			{
				if (ft_lst_insert(token, ft_lstnew_no_malloc(ls->str, WORD, TEXT)) == ERROR_MALLOC)
					return (ft_print_error_malloc(), ft_free_wildcard(&ls), ERROR_MALLOC);
				find = 1;
			}
			if (ls->prev == NULL)
				break ;
			ls = ls->prev;
		}
	}
	else
	{
		if (ft_wildcard_before_and_after(token, ls, &find) == ERROR_MALLOC)
			return (ft_print_error_malloc(), ft_free_wildcard(&ls), ERROR_MALLOC);
	}
	if (find == 1)
		ft_lst_del(token);
	return (ft_free_wildcard(&ls), SUCCESS);
}

int	ft_is_there_wildcard(char *str)
{
	int	index;
	int	count;

	index = -1;
	count = 0;
	while (str[++index])
	{
		if (str[index] == '*')
			count++;
	}
	if (count == 1)
		return (SUCCESS);
	return (1);
}

int	ft_replace_wildcard(t_token **token)
{
	while (*token != NULL)
	{
		if ((*token)->quotes == WORD && (*token)->type == TEXT && ft_is_there_wildcard((*token)->str) == SUCCESS)
		{
			if (ft_insert_wildcard(token) != SUCCESS)
				return (ERROR);
		}
		if ((*token)->next == NULL)
			break ;
		else
			*token = (*token)->next;
	}
	while (token != NULL)
	{
		if ((*token)->prev == NULL)
			break ;
		else
			*token = (*token)->prev;
	}
	return (SUCCESS);
}
