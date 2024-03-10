/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:52:38 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/11 00:17:05 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

int set_main_1(t_tree **tree, int *exit_status, int argc, char **argv)
{
	*tree = NULL;
	*exit_status = 0;
	(void)argv;
	if (argc != 1)
		return (ERROR);
	if (ft_set_sig() == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int set_main_2(char ***env, char **envp)
{
	*env = ft_copy_env(envp);
	if (*env == NULL)
		return (ERROR_MALLOC);
	return (SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_data_parse	data_parse;
	t_tree			*tree;
	int				exit_status;
	char			**env;
	int				tmp;

	if (set_main_1(&tree, &exit_status, argc, argv) || set_main_2(&env, envp))
		return (ERROR);
	while (1)
	{
		data_parse.prompt = ft_get_prompt();
		if (data_parse.prompt == NULL)
			return (ERROR_PROMPT);
		data_parse.input = readline(data_parse.prompt);
		free(data_parse.prompt);
		tree = NULL;
		if (data_parse.input == NULL)
		{	
			rl_clear_history();
			ft_putstr_fd("exit\n", 1);
			return (free_tab_tab(env), 0);
		}
		if (ft_parse(&tree, &data_parse, env, exit_status) == GOOD_INPUT)
		{
			tmp = g_signal;
			g_signal = -100;
			exit_status = ft_tree_exec(tree, &env, &exit_status);
			if (exit_status == ERROR_MALLOC)
				return (free_and_close_tree(tree), free(env), ERROR_MALLOC);
			free_and_close_tree(tree);
			g_signal = tmp;
		}
	}
	return (exit_status);
}