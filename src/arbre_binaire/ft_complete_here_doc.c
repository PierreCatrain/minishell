/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_complete_here_doc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 02:57:01 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/02 14:32:47 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_nb_here_doc(t_token *token)
{
    int count;

    count = 0;
    while (token != NULL)
    {
        if (token->type == HEREDOC)
            count++;
        token = token->next;
    }
    return (count);
}

int ft_complete_here_doc(t_data_parse *data_parse, t_token *token)
{
    int index;
    //int tmp;

    //tmp = g_exit_status;
    //g_exit_status = -100;
    index = 0;
    data_parse->index_here_doc = ft_nb_here_doc(token) - 1;
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
	        data_parse->array_here_doc[index] = open(data_parse->heredoc, O_CREAT | O_RDWR | O_TRUNC, 0644);
	        if (ft_complete(data_parse->array_here_doc[index++], token) == ERROR)
            {
                unlink(data_parse->heredoc);
	            free(data_parse->heredoc);
                return (ERROR);
            }
	        unlink(data_parse->heredoc);
	        free(data_parse->heredoc);
        }
        token = token->next;
    }
    //g_exit_status = tmp;
    return (SUCCESS);
}