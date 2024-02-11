/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_binary_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 01:19:42 by lgarfi            #+#    #+#             */
/*   Updated: 2024/02/09 19:07:11 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

// si c'est un && faire celui de gauche s'il est bon faire celui de droite
// si c'est un || faire celui de gauche s'il est bon on arrete s'il n'est pas bon on fait l'autre
// est ce que l'ordre est correct dans l'arbre ? si oui la commande est situe dans l'enfant de droite ?
// si oui qu'est ce que lst_exec

// fonction qui execute commande par commande : 

void	print_linked_list(t_lst_exec *lst_exec)
{
	t_lst_exec *tmp;

	tmp = lst_exec;
	while (tmp)
	{
		print_tab_tab(tmp->args);
		tmp = tmp->next;
	}
}

void	ft_tree_exec(t_tree *tree, char **env)
{
	if (tree->left_child)
		ft_tree_exec(tree->left_child, env);
	if (tree->type == OPPERATOR_AND && g_exit_status == 0)
		ft_exec_cmd_fork(tree->right_child, env);
	else if (tree->type == OPPERATOR_OR && g_exit_status != 0)
		ft_exec_cmd_fork(tree->right_child, env);
	else if (tree->type == EXEC_LIST)
	{
		while (tree->lst_exec != NULL)
		{
			printf("lst exec wwwww:\n");
			print_linked_list(tree->lst_exec);
			printf("1\n");
			ft_exec_cmd_fork(tree, env);
			printf("2\n");
			tree->lst_exec = tree->lst_exec->next;
		}
	}
	// else
	// 	ft_tree_exec(tree->right_child, env);
	return;
	// executer l'enfant de droite en fonction du type du parent et du retour de la commande de l'enfant de droite
}