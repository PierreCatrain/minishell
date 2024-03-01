/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:52:38 by picatrai          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/02/27 07:19:07 by picatrai         ###   ########.fr       */
=======
/*   Updated: 2024/03/01 13:31:08 by picatrai         ###   ########.fr       */
>>>>>>> 4a2c2c7cc4cd1b25115ddc16a6bea9f257eb41a8
/*                                                                            */
/* ************************************************************************** */


#include <minishell.h>

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
	rl_clear_history();
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
	// if (ft_check_argc_envp(argc, argv) == ERROR_ARGC_ENVP)
	// 	return (ERROR_ARGC_ENVP);
	env = dup_env(envp);// peut etre le faire depuis l'exec
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
			free_2d(env);
			free(data_parse.input);
<<<<<<< HEAD
			ft_exit(NULL);
=======
			ft_putstr_fd("exit\n", 1);
>>>>>>> 4a2c2c7cc4cd1b25115ddc16a6bea9f257eb41a8
			return (0);
		}
		if (is_input_only_whitespace(data_parse.input))
			add_history(data_parse.input);
		if (ft_parse(&tree, &data_parse) == GOOD_INPUT)
		{
			//exit_status = ft_tree_exec(tree, &env, &exit_status);
			free_and_close_tree(tree);
		}
	}
	return (exit_status);
}


//cd En travaux/

/*
a faire

"" pas de tokens

le leak de l'historique
signaux + gerer si on ctrl c ou d depuis le remplissage du here_doc et attention on a open mais pas re close puis re open
ctrl c depuis une commande


ameliorer
echo doit echo tout les args
les erreurs d'invalide tokens
*/
