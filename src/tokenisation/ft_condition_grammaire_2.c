/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_condition_grammaire_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 01:08:04 by picatrai          #+#    #+#             */
/*   Updated: 2024/02/27 00:39:13 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_check_pipes(t_token *token)
{
	if (token->type == PIPE || ft_lstlast(token)->type == PIPE)
		return (WRONG_INPUT);
	while (token->next != NULL)
	{
		if (token->type == PIPE && (token->next->type == OR \
		|| token->next->type == AND || token->next->type == OPEN_PARENTHESIS \
		|| token->next->type == CLOSE_PARENTHESIS \
		|| token->next->type == INFILE || token->next->type == OUTFILE \
		|| token->next->type == HEREDOC || token->next->type == APPEND))
			return (WRONG_INPUT);
		if ((token->type == OR || token->type == AND \
		|| token->type == OPEN_PARENTHESIS || token->type == CLOSE_PARENTHESIS \
		|| token->type == INFILE || token->type == OUTFILE \
		|| token->type == HEREDOC || token->type == APPEND) \
		&& token->next->type == PIPE)
			return (WRONG_INPUT);
		if (token->type == PIPE && token->next->type == PIPE)
			return (WRONG_INPUT);
		token = token->next;
	}
	return (GOOD_INPUT);
}

int	is_redirection_well_followed(t_token *token)
{
	while (token->next != NULL)
	{
		if (token->type == INFILE && token->next->type != INFILE_TEXT)
			return (print_invalid_token("<"), WRONG_INPUT);
		else if (token->type == OUTFILE && token->next->type != OUTFILE_TEXT)
			return (print_invalid_token(">"), WRONG_INPUT);
		else if (token->type == HEREDOC && token->next->type != HEREDOC_TEXT)
			return (print_invalid_token("<<"), WRONG_INPUT);
		else if (token->type == APPEND && token->next->type != APPEND_TEXT)
			return (print_invalid_token(">>"), WRONG_INPUT);
		token = token->next;
	}
	if (token->type == INFILE && token->next == NULL)
		return (print_invalid_token("<"), WRONG_INPUT);
	else if (token->type == OUTFILE && token->next == NULL)
		return (print_invalid_token(">"), WRONG_INPUT);
	else if (token->type == HEREDOC && token->next == NULL)
		return (print_invalid_token("<<"), WRONG_INPUT);
	else if (token->type == APPEND && token->next == NULL)
		return (print_invalid_token(">>"), WRONG_INPUT);
	return (GOOD_INPUT);
}
