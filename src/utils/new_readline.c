/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_readline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:02:47 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/07 15:04:52 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int ft_set_new_gnl()
// {
    
// }

char *new_readline(char *lim)
{
    char *new;
	char *res;
    char *read_str;
    int size;

    new = malloc(sizeof(char));
    if (new == NULL)
        return (NULL);
    new[0] = '\0';
    read_str = malloc(2 * sizeof(char));
	if (read_str == NULL)
		return (free(new), NULL);
	read_str[0] = '\0';
    size = read(0, read_str, 1);
    while (size > 0)
    {
        read_str[1] = '\0';
		if (read_str[0] == '\n')
		{
            new = ft_join_char(new, read_str[0]);
            if (new == NULL)
                return (free(read_str), NULL);
			return (free(read_str), new);
		}
        else
        {
            new = ft_join_char(new, read_str[0]);
            if (new == NULL)
                return (free(read_str), NULL);
        }
        size = read(0, read_str, 1);
    }
    if (size == -1)
    {
        printf("\n");
		return (free(new), free(read_str), NULL);
    }
    if (size == 0)
    {
        printf("\n");
        ft_putstr_fd("minishell: warning: heredoc wanted (`", 2);
        ft_putstr_fd(lim, 2);
        ft_putstr_fd("')\n", 2);
		return (free(new), free(read_str), NULL);
    }
    res = ft_strdup(new);
    if (res == NULL)
        return (free(new), free(read_str), NULL);
    return (free(new), free(read_str), res);
}

// new = ft_join_char(new, read_str[0]);
// if (new == NULL)
//     return (free_2d(str), free(read_str), NULL);
// // printf("str |%s|\n", new);
// str = ft_add_to_2d(str, new);
// if (str == NULL)
//     return (free(read_str), NULL);
// free(new);
// new = malloc(sizeof(char));
// if (new == NULL)
//     return (free_2d(str), free(read_str), NULL);
// new[0] = '\0';
// // return (free_2d(str), free(read_str), new);
// break ;