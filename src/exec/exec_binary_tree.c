/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_binary_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 01:19:42 by lgarfi            #+#    #+#             */
/*   Updated: 2024/02/26 14:43:50 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

// si c'est un && faire celui de gauche s'il est bon faire celui de droite
// si c'est un || faire celui de gauche s'il est bon on arrete s'il n'est pas bon on fait l'autre
// est ce que l'ordre est correct dans l'arbre ? si oui la commande est situe dans l'enfant de droite ?
// si oui qu'est ce que lst_exec

// fonction qui execute commande par commande : 

void	ft_free_tab_tab_incremented(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
}

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

char	*ft_strjoin_wihtout_free(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	str = (char *) malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = -1;
	while (s2[++j])
		str[i + j] = s2[j];
	str[i + j] = '\0';
	return (str);
	
}

int	ft_tree_exec(t_tree *tree, char ***env, int *status)
{
	t_tree	*tmp_tree = NULL;
	int		ll_len;
	int		status2;
	char	**arg;

	ll_len = 0;
	tmp_tree = tree;
	if (tmp_tree->left_child)
		ft_tree_exec(tmp_tree->left_child, env, status);
	if (tmp_tree->type == OPPERATOR_AND && *status == 0)
		ft_tree_exec(tmp_tree->right_child, env, status);// tree-> right child
	if (tmp_tree->type == OPPERATOR_OR && *status != 0)
		ft_tree_exec(tmp_tree->right_child, env, status);
	if (tmp_tree->type == EXEC_LIST)
	{
		arg = new_args(tmp_tree->lst_exec->args);
		ll_len = ft_linked_list_size(tmp_tree->lst_exec);
		if (ll_len == 1 && ft_is_builtin(arg[0]) == 1)
		{
			printf("c'est un builtin\n");
			status2 = ft_find_builtin(arg[0], arg, env); //EXECUTE BUILTIN
			free_tab_tab(arg);
			return (*status);
		}
		while (tmp_tree->lst_exec != NULL)
		{
			ft_exec_cmd_fork(tmp_tree, env, arg);
			tmp_tree->lst_exec = tmp_tree->lst_exec->next;
		}
		free_tab_tab(arg);
		while ((--ll_len) + 1 > 0)
			waitpid(0, status, 0);
	}
	if (WIFEXITED(*status))
		return(WEXITSTATUS(*status));
	return (0);
}
// mettre le retour de cette valeur dans une variable et retourner la derniere
