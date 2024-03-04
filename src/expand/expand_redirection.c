/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 06:57:07 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/04 17:59:02 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_ambiguous_redirect(char *str)
{
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(str, 2);
    ft_putstr_fd(": ambiguous redirect\n", 2);
    free(str); 
    return (NULL);
}

char *ft_find_wildcard(char *str, t_wildcard *ls, char **split)
{
    int found;
    char *new;
    int index;

    found = 0;
    while (ls != NULL)
	{
		if (ft_check_before(str, split, ls->str) && ft_check_after(str, split, ls->str) && ft_check_all(split, ls->str))
		{
            if (found == 0)
            {
                new = ft_strdup(ls->str);
		        if (new == NULL)
			        return (free_2d(split), free(str), NULL);
            }
            else
            {
                index = -1;
                while (split[++index])
                {
                    if (split[index] != NULL)
                        free(split[index]);
                }
                free(split);
                return (free(new), ft_ambiguous_redirect(str));
            }
			found++;
		}
        if (ls->next != NULL)
		    ls = ls->next;
        else
            break;
	}
    free_2d(split);
	if (found == 0)
		return (str);
    return (free(str), new);
}

char *ft_transfo_wildcard(char *str, t_wildcard *ls)
{
    char **split;

    if (ft_occ(str, '*') == 0)
    {
        return (str);
    }
	split = ft_split(str, '*');
	if (split == NULL)
		return (free(str), NULL);
	return (ft_find_wildcard(str, ls, split));
}

char *transfo_expand(char *str, t_expand *expand, t_data_parse *data_parse)
{
    char *new;
    t_wildcard *ls;

    ls = NULL;
    new = ft_replace_env_variable(str, expand, 0);
    if (new == NULL)
        return (NULL);
    if (set_ls(&ls) != SUCCESS)
		return (NULL);
    new = ft_transfo_wildcard(new, ls);
    if (new == NULL)
        return (ft_free_wildcard(&ls), free_expand(data_parse->expand, ft_strlen_2d(data_parse->args_tmp)), free_2d(data_parse->args_tmp), NULL);
    return (ft_free_wildcard(&ls), new);
}
