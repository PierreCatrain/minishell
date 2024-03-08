/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:52:38 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/08 19:43:40 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

int	only_one_cmd(t_tree *tree, char **argv, char ***env, int *exit_status)
{
	t_data_parse	data_parse;

	data_parse.input = ft_strdup(argv[2]);
	if (data_parse.input == NULL)
		return (ERROR_MALLOC);
	add_history(data_parse.input);
	if (ft_parse(&tree, &data_parse) == GOOD_INPUT)
		ft_tree_exec(tree, env, exit_status);
	free_and_close_tree(tree);
	rl_clear_history();
	free_tab_tab(*env);
	return (*exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	t_data_parse	data_parse;
	t_tree			*tree;
	int				exit_status;
	char			**env;

	tree = NULL;
	exit_status = 0;
	if (ft_set_sig() == ERROR)
		return (ERROR);
	if (ft_check_argc(argc, argv) == ERROR_ARGC_ENVP)
		return (ERROR_ARGC_ENVP);
	env = ft_copy_env(envp);
	if (!env)
		return (ERROR_MALLOC);
	if (argc == 3)
		return (only_one_cmd(tree, argv, &env, &exit_status));
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
			free(data_parse.input);
			free_tab_tab(env);
			rl_clear_history();
			ft_putstr_fd("exit\n", 1);
			return (0);
		}
		if (is_input_only_whitespace(data_parse.input))
			add_history(data_parse.input);
		if (ft_parse(&tree, &data_parse) == GOOD_INPUT)
		{
			exit_status = ft_tree_exec(tree, &env, &exit_status);
			if (exit_status == ERROR_MALLOC)
				return (free_and_close_tree(tree), free(env), ERROR_MALLOC);
			free_and_close_tree(tree);
		}
	}
	return (exit_status);
}
