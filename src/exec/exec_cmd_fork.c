/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:38:07 by lgarfi            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/03/01 09:24:00 by picatrai         ###   ########.fr       */
=======
/*   Updated: 2024/03/01 11:54:51 by picatrai         ###   ########.fr       */
>>>>>>> 4a2c2c7cc4cd1b25115ddc16a6bea9f257eb41a8
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

// recois une liste chaine si la liste en plus grande que 1, alors il y a des pipes et donc faire 
// la fonction qui

<<<<<<< HEAD
int	ft_exec_cmd_fork(t_tree *tree, char ***env, int *tab_pid)
{
	pid_t	pid;
	char	**arg;

	print_tab_tab(tree->lst_exec->args);
	arg = ft_new_args(tree->lst_exec); // a quoi ca sert ?
	print_tab_tab(arg);
	// printf("dans cmd fork fd in = %d fd out = %d\n", tree->lst_exec->fd_in, tree->lst_exec->fd_out);
=======
int	ft_exec_cmd_fork(t_tree *tree, char ***env, char **args)
{
	pid_t	pid;
	char	**arg;
	int		tmp;

>>>>>>> 4a2c2c7cc4cd1b25115ddc16a6bea9f257eb41a8
	if (tree->lst_exec->fd_in == -1 || tree->lst_exec->fd_out == -1)
	{
		// gestion d'erreur
		return (2) ;
		// return (EXIT_FAILURE); est ce que reurn un exit failure a une utilite ?
	}
<<<<<<< HEAD
	pid = fork();
	if (pid == -1)
	{
		printf("%s\n",  strerror(errno));
=======
	tmp = g_exit_status;
	pid = fork();
	if (pid == -1)
	{
>>>>>>> 4a2c2c7cc4cd1b25115ddc16a6bea9f257eb41a8
		return (EXIT_FAILURE);
		// gestion d'err
	}
	if (pid == 0)
	{
<<<<<<< HEAD
		// printf("fin %d\n", tree->lst_exec->fd_out);
		// printf("qwer\n");
		//arg = ft_new_args(tree->lst_exec); // a quoi ca sert ?
		dup2(tree->lst_exec->fd_in, 0);
		dup2(tree->lst_exec->fd_out, 1);
		free_and_close_tree(tree);
		// free(tab_pid);
=======
		arg = ft_new_args(tree->lst_exec); // a quoi ca sert ?
		dup2(tree->lst_exec->fd_in, 0);
		dup2(tree->lst_exec->fd_out, 1);
		free_and_close_tree(tree);
		free_tab_tab(args);
>>>>>>> 4a2c2c7cc4cd1b25115ddc16a6bea9f257eb41a8
		find_cmd(env, arg);
	}
	else
	{
<<<<<<< HEAD
=======
		g_exit_status = -100;
>>>>>>> 4a2c2c7cc4cd1b25115ddc16a6bea9f257eb41a8
		if (tree->lst_exec->fd_out > 2)
			close(tree->lst_exec->fd_out);
		if (tree->lst_exec->fd_in > 2)
			close(tree->lst_exec->fd_in);
<<<<<<< HEAD
		(*tab_pid) = pid;
	
	}
	return (2);
=======
	}
	return (tmp);
>>>>>>> 4a2c2c7cc4cd1b25115ddc16a6bea9f257eb41a8
}

// int	main(int ac, char **av, char **env)
// {
// 	(void)ac;
// 	printf("%d\n", ft_exec_cmd_fork(0, 1, av + 1, env));
// }