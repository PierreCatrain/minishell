/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 06:57:07 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/03 10:29:02 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_ambiguous_redirect(char *str)
{
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(str, 2);
    ft_putstr_fd(": ambiguous redirect\n", 2);
    return (NULL);
}

char *ft_find_wildcard(char *str, t_wildcard *ls, char **split)
{
    int found;
    char *new;

    found = 0;
    while (ls->next != NULL)
	{
		if (ft_check_before(str, split, ls->str) && ft_check_after(str, split, ls->str) && ft_check_all(split, ls->str))
		{
            if (found == 0)
            {
                new = ft_strdup(ls->str);
		        if (new == NULL)
			        return (free_2d(split), NULL);
            }
            else
                return (free_2d(split), ft_ambiguous_redirect(str));
			found++;
		}
		ls = ls->next;
	}
    free_2d(split);
	if (found == 0)
			return (str);
    return (new);
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
		return (NULL);
	return (ft_find_wildcard(str, ls, split));
}

char *transfo_expand(char *str, t_expand *expand)
{
    char *new;
    t_wildcard *ls;

    ls = NULL;
    new = ft_replace_env_variable(str, expand);
    if (new == NULL)
        return (NULL);
    if (set_ls(&ls) != SUCCESS)
		return (NULL);
    new = ft_transfo_wildcard(new, ls);
    if (new == NULL)
        return (ft_free_wildcard(&ls), NULL);
    return (ft_free_wildcard(&ls), new);
}

// char *ft_transfo_wildcard(char *str, t_wildcard *ls)
// {
//     char *new;
//     char **split;
//     int found;

//     found = 0;
//     if (ft_occ(str, '*') == 0)
//     {
//         return (str);
//     }
// 	split = ft_split(str, '*');
// 	if (split == NULL)
// 		return (NULL);
// 	while (ls->next != NULL)
// 	{
// 		if (ft_check_before(str, split, ls->str) && ft_check_after(str, split, ls->str) && ft_check_all(split, ls->str))
// 		{
//             if (found == 0)
//             {
//                 new = ft_strdup(ls->str);
// 		        if (new == NULL)
// 			        return (NULL);
//             }
//             else
//                 return (ft_ambiguous_redirect(str));
// 			found++;
// 		}
// 		ls = ls->next;
// 	}
// 	if (found == 0)
// 			return (str);
//     return (new);
// }