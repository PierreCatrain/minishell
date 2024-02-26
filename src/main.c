/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:52:38 by picatrai          #+#    #+#             */
/*   Updated: 2024/02/26 01:01:48 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	g_exit_status;

int	only_one_cmd(t_tree *tree, char **argv, char ***env)
{
	t_data_parse	data_parse;
	int				exit_status;

	exit_status = 0;
	data_parse.input = ft_strdup(argv[2]);
	if (data_parse.input == NULL)
		return (ERROR_MALLOC);
	add_history(data_parse.input);
	if (ft_parse(&tree, &data_parse) == GOOD_INPUT)
		exit_status = ft_tree_exec(tree, env);
	rl_clear_history();
	return (exit_status);
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
	// if (ft_check_argc_envp(argc, argv) == ERROR_ARGC_ENVP)
	// 	return (ERROR_ARGC_ENVP);
	env = dup_env(envp);// peut etre le faire depuis l'exec
	if (argc == 3)
		return (only_one_cmd(tree, argv, &env));
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
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		if (is_input_only_whitespace(data_parse.input))
			add_history(data_parse.input);
		if (ft_parse(&tree, &data_parse) == GOOD_INPUT)
		{
			exit_status = ft_tree_exec(tree, &env);
			printf("exit status = %d\n", exit_status);
			free_and_close_tree(tree);
		}
	}
	// printf("exit status = %d\n", exit_status);
	return (exit_status);
}

//echo bonjour"v"sfa

/*
a faire

le leak de l'historique
signaux + gerer si on ctrl c ou d depuis le remplissage du here_doc et attention on a open mais pas re close puis re open
ctrl c depuis une commande


ameliorer
echo doit echo tout les args
les erreurs d'invalide tokens
*/
