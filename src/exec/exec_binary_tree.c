/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_binary_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 01:19:42 by lgarfi            #+#    #+#             */
/*   Updated: 2024/02/22 19:27:47 by lgarfi           ###   ########.fr       */
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

char	*ft_get_err_msg(char *cmd, char *msg)
{
	char	*err_msg = NULL;
	char	*cmd_mall = NULL;
	char	*err_msg_mall = NULL;

	err_msg = (char *) malloc(sizeof(char) * (ft_strlen(cmd) + ft_strlen(msg) + 1));
	// ajouter a gc si err del gc exit
	cmd_mall = ft_str_dup_env(cmd, cmd_mall);
	err_msg_mall = ft_str_dup_env(msg, err_msg_mall);
	err_msg = ft_strjoin_wihtout_free(cmd_mall, err_msg_mall);
	return (free(err_msg_mall), err_msg);
}

int	ft_test_err_msg(t_tree *tree, char *err_msg)
{
	char	*cmd_path;
	char	**path_split;
	char	**cmd;

	cmd = new_args(tree->lst_exec->args);
	if (!cmd)
		return (ERROR_MALLOC);
	path_split = ft_get_path_cmd(); // marche pas
	if (!path_split)
		return (ERROR_MALLOC);
	while (*path_split)
	{
		cmd_path = ft_strjoin_path(*path_split, cmd[0]);
		if (cmd_path == NULL)
		{
			return (ERROR_MALLOC);
			// gestion d'erreur
		}
		if (!access(cmd_path, F_OK | X_OK))
		{
			free(cmd_path);
			free_tab_tab(cmd);
			path_split++;
			ft_free_tab_tab_incremented(path_split);
			err_msg = ft_strdup("n");
			return (0);
		}
		free (cmd_path);
		path_split++;
	}
	err_msg = ft_strjoin_wihtout_free(cmd[0], ": command not found\n");
	free_tab_tab(cmd);
	return (1);
}

void	ft_test_all_err_msg(t_tree *tree, char **tab_err_msg, int nb_of_cmd)
{
	int	i;
	t_tree	*tmp;

	i = 0;
	tmp = tree;
	while (i < nb_of_cmd)
	{
		ft_test_err_msg(tmp, tab_err_msg[i]);
		i++;
		tmp->lst_exec = tmp->lst_exec->next;
	}
}

int	ft_tree_exec(t_tree *tree, char ***env)
{
	t_tree	*tmp_tree = NULL;
	char	**arg;
	int		status;
	int		ll_len;
	int		*tab_pid;
	int		*tmp_pid;
	int		i;
	
	ll_len = ft_linked_list_size(tree->lst_exec);
	arg = new_args(tree->lst_exec->args);
	tab_pid = (int *) malloc (sizeof(int) * ll_len);
	// ajouter a gc si err del gc exit
	tmp_pid = tab_pid;
	if (tree->left_child)
		ft_tree_exec(tree->left_child, env);
	if (tree->type == OPPERATOR_AND && g_exit_status == 0)
		ft_exec_cmd_fork(tree, env, tmp_pid++);// tree-> right child
	else if (tree->type == OPPERATOR_OR && g_exit_status != 0)
		ft_exec_cmd_fork(tree, env, tmp_pid++);
	else if (tree->type == EXEC_LIST)
	{
		tmp_tree = tree;
		i = 0;
		while (tree->lst_exec != NULL)
		{
			if (ll_len == 1 && ft_is_builtin(arg[0]) == 1)
			{
				status = ft_find_builtin(arg[0], arg, env);
				// gestion memoire
				return (status);
			}
			ft_exec_cmd_fork(tree, env, tmp_pid);
			tree->lst_exec = tree->lst_exec->next;
			tmp_pid++;
			i++;
		}
	}
	i = 0;
	while (ll_len > 0)
	{
		waitpid(tab_pid[i], &status, 0);
		ll_len--;
		i++;
	}
	// guette les free
	if (WIFEXITED(status))
		return(WEXITSTATUS(status));
	return (0);
}
// mettre le retour de cette valeur dans une variable et retourner la derniere
