/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_binary_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 01:19:42 by lgarfi            #+#    #+#             */
/*   Updated: 2024/02/25 23:02:09 by lgarfi           ###   ########.fr       */
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

int	ft_tree_exec(t_tree *tree, char ***env)
{
	t_tree	*tmp_tree = NULL;
	t_lst_exec	*tmp_lst_exec;
	int		status;
	int		ll_len;
	int		*tab_pid;
	int		*tmp_pid;
	int		i;

	status = 0;
	tab_pid = NULL;
	// ajouter a gc si err del gc exit
	printf("enfant de gauche n'existe pas\n");
	if (tree->left_child)
	{	
		printf("1\n");
		// printf("je descend sur l'enfant de gauche\n");
		// printf("status = %d\n", status);
		ft_tree_exec(tree->left_child, env);
	}
	if (tree->type == OPPERATOR_AND && status == 0)
	{
		printf("2\n");
		// printf("operateur && j'exec cmd fork avec tree->right\n tree->right->commande = %s\n", tree->right_child->lst_exec->args[0]);
		// printf("status = %d\n", status);
		ft_tree_exec(tree->right_child, env);// tree-> right child
	}
	else if (tree->type == OPPERATOR_OR && status != 0)
	{
		printf("3\n");
		// printf("operateur || j'exec cmd fork avec tree->right\n tree->right->commande = %s\n", tree->right_child->lst_exec->args[0]);
		// printf("status = %d\n", status);
		ft_tree_exec(tree->right_child, env);
	}
	else if (tree->type == EXEC_LIST)
	{
		printf("4\n");
		// printf("jexec une liste chaine de commande\n");
		// printf("status = %d\n", status);
		ll_len = ft_linked_list_size(tree->lst_exec);
		tab_pid = (int *) malloc (sizeof(int) * ll_len);
		tmp_pid = tab_pid;
		tmp_tree = tree;
		tmp_lst_exec = tree->lst_exec;
		if (ll_len == 1 && ft_is_builtin(tree->lst_exec->args[0]) == 1)
		{
			printf("dans builtin");
			status = ft_find_builtin(tree->lst_exec->args[0], tree->lst_exec->args, env); //EXECUTE BUILTIN
			// gestion memoire
			free(tab_pid);
			return (status);
		}
		while (tmp_lst_exec != NULL)
		{
			printf("boucle command\n");
			ft_exec_cmd_fork(tree, env, tmp_pid);
			tmp_lst_exec = tmp_lst_exec->next;
			tmp_pid++;
		}
		// printf("ll_len = %d\n", ll_len);
		i = 0;
		printf("fin boucle commande\n");
		while (ll_len > 0)
		{
			waitpid(tab_pid[i], &status, 0);
			// printf("tab_pid[%d] = %d\n", i, tab_pid[i]);
			ll_len--;
			i++;
		}
		printf("5\n");
		free(tab_pid);
	}
	// guette les free
	if (WIFEXITED(status))
		return(WEXITSTATUS(status));
	return (0);
}
// mettre le retour de cette valeur dans une variable et retourner la derniere
