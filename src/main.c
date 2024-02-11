/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:52:38 by picatrai          #+#    #+#             */
/*   Updated: 2024/02/11 04:43:08 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_exec(t_tree *tree, char **envp)
{
	tree = (t_tree *)tree;
	envp = (char **)envp;
	free_and_close_tree(tree);
	//rl_clear_history();
	return (SUCCESS);
}

int	only_one_cmd(t_tree *tree, char **argv, char **envp)
{
	t_data_parse	data_parse;

	data_parse.input = ft_strdup(argv[2]);
	if (data_parse.input == NULL)
		return (ERROR_MALLOC);
	add_history(data_parse.input);
	if (ft_parse(&tree, &data_parse) == GOOD_INPUT)
		ft_exec(tree, envp);
	rl_clear_history();
	return (SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_data_parse	data_parse;
	t_tree			*tree;

	tree = NULL;
	if (ft_check_argc_envp(argc, argv) == ERROR_ARGC_ENVP)
		return (ERROR_ARGC_ENVP);
	if (argc == 3)
		return (only_one_cmd(tree, argv, envp));
	while (1)
	{
		data_parse.prompt = ft_get_prompt();
		if (data_parse.prompt == NULL)
			return (ERROR_PROMPT);
		data_parse.input = readline(data_parse.prompt);
		free(data_parse.prompt);
		tree = NULL;
		if (is_input_only_whitespace(data_parse.input))
		{
			add_history(data_parse.input);
			if (ft_parse(&tree, &data_parse) == GOOD_INPUT)
				ft_exec(tree, envp);
		}
	}
	return (SUCCESS);
}

//echo bonjour"v"sfa

/*
a faire

le leak de l'historique
signaux + gerer si on ctrl c ou d depuis le remplissage du here_doc et attention on a open mais pas re close puis re open
$?

ameliorer

les erreurs d'invalide tokens
le variable d'env
*/
