/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:52:38 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/05 11:37:32 by picatrai         ###   ########.fr       */
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
	if (ft_parse(&tree, &data_parse, *env, *exit_status) == GOOD_INPUT)
		ft_tree_exec(tree, env, exit_status);
	free_and_close_tree(tree);
	rl_clear_history();
	free_tab_tab(*env);
	return (*exit_status);
}

int	count_word(int nb)
{
	int	count;

	count = 1;
	while (nb >= 10)
	{
		nb /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa_shlvl(int nb)
{
	char	*str;
	int		len;
	int		i;

	len = count_word(nb);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	str[len] = '\0';
	while (0 < len)
	{
		str[len - 1] = (nb % 10) + '0';
		nb /= 10;
		len--;
	}
	return (str);
}

int	ft_atoi_int_shlvl(char *nb)
{
	int	i;
	int	res;
	int	s;

	i = 0;
	res = 0;
	s = 1;
	if (nb[0] == '-')
		s = -1;
	while (nb[i] == '-' || nb[i] == '+')
		i++;
	while (nb[i] >= '0' && nb[i] <= '9')
	{
		res = res * 10 + nb[i] - 48;
		i++;
	}
	res += 1;
	if ((res * s) < 0 || (res * s) > 2147483647)
		return (1);
	return (s * res);
}

char	*ft_change_shlvl(char *shlvl)
{
	char	*res_val;
	char	*res;

	res_val = ft_itoa_shlvl(ft_atoi_int_shlvl(shlvl));
	if (!res_val)
		return (NULL);
	res = ft_strjoin_wihtout_free("SHLVL=", res_val);
	if (!res)
		return (NULL);
	free(res_val);
	return (res);
}

char	**ft_copy_env(char **envp)
{
	char	**env;
	int		len_envp;
	int		i;
	char	*envp_name;

	if (!envp)
		return (NULL);
	len_envp = ft_strlen_2d(envp);
	env = (char **) malloc(sizeof(char *) * (len_envp + 2));
	i = -1;
	while (envp[++i])
	{
		envp_name = ft_find_export_name(envp[i]);
		if (ft_strcmp(envp_name, "SHLVL") == 0)
		{
			env[i] = ft_change_shlvl(getenv("SHLVL"));
			free(envp_name);
			continue ;
		}
		free(envp_name);
		env[i] = ft_str_dup_env(envp[i], env[i]);
	}
	env[i] = NULL;
	return (env);
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
	if (!envp[0])
	{
		printf("pas d'env\n");
		return (2);
	}
	env = ft_copy_env(envp);
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
		if (ft_parse(&tree, &data_parse, env, exit_status) == GOOD_INPUT)
		{
			exit_status = ft_tree_exec(tree, &env, &exit_status);
			if (exit_status == ERROR_MALLOC)
				return (free_and_close_tree(tree), free(env), ERROR_MALLOC);
			free_and_close_tree(tree);
		}
		printf("exit_status = %d\n", exit_status);
	}
	return (exit_status);
}