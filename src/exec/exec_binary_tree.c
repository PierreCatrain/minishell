/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_binary_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 01:19:42 by lgarfi            #+#    #+#             */
/*   Updated: 2024/02/09 17:34:26 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

// si c'est un && faire celui de gauche s'il est bon faire celui de droite
// si c'est un || faire celui de gauche s'il est bon on arrete s'il n'est pas bon on fait l'autre
// est ce que l'ordre est correct dans l'arbre ? si oui la commande est situe dans l'enfant de droite ?
// si oui qu'est ce que lst_exec

// fonction qui execute commande par commande : 

void	ft_tree_exec(t_tree *tree, char **env)
{
	if (tree->left_child)
		ft_tree_exec(tree->left_child, env);
	if (tree->type == OPPERATOR_AND && g_exit_status == 0)
	{
		ft_exec_cmd_fork(tree->right_child, env);
		printf("1\n");
	}
	else if (tree->type == OPPERATOR_OR && g_exit_status != 0)
	{
		ft_exec_cmd_fork(tree->right_child, env);
		printf("2\n");
	}
	else if (tree->type == EXEC_LIST)
	{
		ft_exec_cmd_fork(tree, env);
		printf("commande = %s\n", tree->lst_exec->args[0]);
		printf("exit status = %lld\n", g_exit_status);
	}
	// else
	// 	ft_tree_exec(tree->right_child, env);
	return;
	// executer l'enfant de droite en fonction du type du parent et du retour de la commande de l'enfant de droite
}