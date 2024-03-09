/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_AST.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 01:19:42 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/10 00:35:18 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset_path(char **path)
{
	static int	free_path;

	free_path = 0;
	if (free_path++ == 0)
		free(*path);
	return (0);
}

char	*ft_get_path(void)
{
	char	*path;

	path = ft_strdup("PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
	if (!path)
		return (NULL);
	return (path);
}

void	ft_replace_last_command(char ***env, char *str)
{
	char	*val;
	int		i;
	char	*export_name;

	i = 0;
	while ((*env)[i])
	{
		export_name = ft_find_export_name((*env)[i]);
		if (ft_strcmp("_", export_name) == 0)
		{
			val = ft_strjoin_wihtout_free("_=", str);
			free(export_name);
			free((*env)[i]);
			(*env)[i] = ft_str_dup_env(val, (*env)[i]);
			free(val);
			return ;
		}
		free(export_name);
		i++;
	}
}

int	ft_tree_exec(t_tree *tree, char ***env, int *status)
{
	int			ll_len;
	int			status2;
	char		**arg;
	int			exit_flag;
	t_tab_pid	pid;

	ll_len = 0;
	arg = NULL;
	if (tree->left_child)
		ft_tree_exec(tree->left_child, env, status);
	if (tree->type == OPPERATOR_AND && *status == 0)
		ft_tree_exec(tree->right_child, env, status);
	if (tree->type == OPPERATOR_OR && *status != 0)
		ft_tree_exec(tree->right_child, env, status);
	if (tree->type == EXEC_LIST)
	{
		exit_flag = 0;
		ll_len = ft_linked_list_size(tree->lst_exec);
		if (ll_len == 1 && ft_is_builtin(tree->lst_exec->args[0]) == 1)
		{
			ft_replace_last_command(env, tree->lst_exec->args[0]);
			arg = ft_new_args(tree->lst_exec, *status, *env);
			status2 = ft_exec_builtin(arg, env, &exit_flag, tree);
			if (exit_flag || status2 == ERROR_MALLOC)
			{
				free_tab_tab(arg);
				free_and_close_tree(tree);
				free_tab_tab(*env);
				rl_clear_history();
				exit(status2);
			}
			return (free_tab_tab(arg), status2);
		}
		pid.tab_pid = malloc(sizeof(int) * ll_len);
		pid.index = 0;
		while (tree->lst_exec != NULL)
		{
			ft_replace_last_command(env, tree->lst_exec->args[0]);
			status2 = ft_exec_cmd_fork(tree, env, *status, pid);
			// g_exit_status = status2;// j'ai rajouter ca c'est pour les signaux
			if (status2 == ERROR_MALLOC)
				return (ERROR_MALLOC);
			if (tree->lst_exec->next != NULL)
				tree->lst_exec = tree->lst_exec->next;
			else
				break ;
			pid.index++;
		}
		pid.index = 0;
		while ((--ll_len) + 1 > 0)
			waitpid(pid.tab_pid[pid.index++], status, 0);
		free(pid.tab_pid);
		if (WIFEXITED(*status))
			*status = WEXITSTATUS(*status);
	}
	return (*status);
}
