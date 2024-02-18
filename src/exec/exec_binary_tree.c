/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_binary_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 01:19:42 by lgarfi            #+#    #+#             */
/*   Updated: 2024/02/18 17:14:34 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

// si c'est un && faire celui de gauche s'il est bon faire celui de droite
// si c'est un || faire celui de gauche s'il est bon on arrete s'il n'est pas bon on fait l'autre
// est ce que l'ordre est correct dans l'arbre ? si oui la commande est situe dans l'enfant de droite ?
// si oui qu'est ce que lst_exec

// fonction qui execute commande par commande : 

int	ft_linked_list_size(t_lst_exec *lst)
{
	int	len;

	len = 0;
	while (lst != NULL)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}

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

void	ft_tree_exec(t_tree *tree, char ***env)
{
	int	status;
	int	ll_len;

	if (tree->left_child)
		ft_tree_exec(tree->left_child, env);
	if (tree->type == OPPERATOR_AND && g_exit_status == 0)
		ft_exec_cmd_fork(tree->right_child, env);
	else if (tree->type == OPPERATOR_OR && g_exit_status != 0)
		ft_exec_cmd_fork(tree->right_child, env);
	else if (tree->type == EXEC_LIST)
	{
		ll_len = ft_linked_list_size(tree->lst_exec);
		while (tree->lst_exec != NULL)
		{
			ft_exec_cmd_fork(tree, env);
			tree->lst_exec = tree->lst_exec->next;
		}
		while (ll_len >= 0)
		{
			waitpid(0, &status, 0);
			if (WIFEXITED(status))
				g_exit_status = WEXITSTATUS(status);
			ll_len--;
		}
	}
}
