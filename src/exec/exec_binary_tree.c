/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_binary_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 01:19:42 by lgarfi            #+#    #+#             */
/*   Updated: 2024/02/07 21:11:10 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

// si c'est un && faire celui de gauche s'il est bon faire celui de droite
// si c'est un || faire celui de gauche s'il est bon on arrete s'il n'est pas bon on fait l'autre
// est ce que l'ordre est correct dans l'arbre ? si oui la commande est situe dans l'enfant de droite ?
// si oui qu'est ce que lst_exec

// fonction qui execute commande par commande : 

int	exec_and(t_tree *parent)
{
	
}

void	ft_tree_exec(t_tree *tree, char **env)
{
	t_tree	*tmp;
	tmp = tree;
	while (tmp->left_child->left_child)
		tmp = tmp->left_child;
	while (tmp->parent)
	{
		if (tmp->type == OPPERATOR_AND)
			exec_and(tmp->right_child->lst_exec);
		else if (tmp->type == OPPERATOR_OR)
			exec_or(tmp->right_child);
	}
}