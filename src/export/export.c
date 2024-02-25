/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 22:51:52 by lgarfi            #+#    #+#             */
/*   Updated: 2024/02/24 17:53:48 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	ft_is_ascii(char c)
{
	return (!(c >= '0' && c <= '9'));
}

void	free_tab_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

int	ft_strcmp_ascii_order(char *s1, char *s2)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while ((s1[i] || s2[i]) && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	print_tab_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
	{
		printf("tab vide\n");
		return ;
	}
	while (tab[i])
	{
		printf("tab[%d] = %s\n", i, tab[i]);
		i++;
	}
}

void	print_tab_tab_ascii_order(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (ft_strncmp(tab[i], "_=", 2) == 0)
		{
			i++;
			continue;
		}
		printf("declare -x %s\n", tab[i]);
		i++;
	}
}

int	ft_len_tab_tab(char **env)
{
	int	res;

	res = 0;
	while (env[res])
		res++;
	return (res);
}

char	*ft_str_dup_env(char *s1, char *s2)
{
	int	len;
	int	i;

	len = ft_strlen(s1);
	s2 = (char *) malloc(sizeof(char) * (len + 1));
	if (!s2)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*ft_find_export_name(char *str)
{
	int		i;
	int		j;
	char	*export_name;

	i = 0;
	while (str[i] != '=')
		i++;
	export_name = malloc(i + 1);
	if (!export_name)
		return (NULL);
	j = 0;
	while (j < i)
	{
		export_name[j] = str[j];
		j++;
	}
	export_name[j] = '\0';
	return (export_name);
}

int	ft_find_export_index(char **env, char *str)
{
	int		i;
	int		len_str;
	char	*export_name;

	i = 0;
	export_name = ft_find_export_name(str);
	len_str = ft_strlen(export_name);
	if (len_str == 1)
		len_str += 1;
	while (env[i])
	{
		if (ft_strncmp(env[i], str, len_str -1) == 0)
		{
			free(export_name);
			return (i);
		}
		i++;
	}
	free(export_name);
	return (-1);
}

int	ft_is_export_in_env(char **env, char *str)
{
	char	*export_name;
	int		i;
	int		len_str;

	export_name = ft_find_export_name(str);
	if (!export_name)
		return (-1);
	i = 0;
	len_str = ft_strlen(export_name);
	while (env[i] != NULL)
	{
		if (ft_strncmp(str, env[i], len_str) == 0)
		{
			free(export_name);
			return (i);
		}
		i++;
	}
	free(export_name);
	return (0);
}

char	**dup_env(char **env)
{
	int		len_env;
	int		i;
	char	**new_env;

	len_env = ft_len_tab_tab(env);
	new_env = (char **) malloc(sizeof(char *) * (len_env + 2));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i])
	{

		new_env[i] = ft_str_dup_env(env[i], new_env[i]);
		if (!new_env)
			return (NULL);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

char	**dup_env_ascii_order(char **env)
{
	int		len_env;
	int		i;
	char	**new_env;

	len_env = ft_len_tab_tab(env);
	new_env = (char **) malloc(sizeof(char *) * (len_env + 2));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_str_dup_env(env[i], new_env[i]);
		if (!new_env)
			return (NULL);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

void	ft_change_export(char ***env, char *str)
{
	int	index_export;
	int	i;

	index_export = ft_find_export_index(*env, str);
	if (index_export == -1)
		return ;
	i = 0;
	while (i < index_export)
		i++;
	free((*env)[i]);
	(*env)[i] = ft_str_dup_env(str, (*env)[i]);
}

int	ft_check_export_name(char *str)
{
	int			i;
	int			j;
	static char	except[25] = "!\\[]@#$%^&*()+=/?.,`~\" ";

	j = 0;
	while (except[j])
	{
		i = 0;
		while (str[i] && str[i] != '=')
		{
			if (str[i] == except[j])
				return (0);
			i++;
		}
		j++;
	}
	return (1);
}

int	ft_find_back_s(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (str[i])
	{
		if (str[i] == '\\')
			count++;
		i++;
	}
	if (count > 1)
		return (0);
	return (1);
}

void	ft_add_export_value(char **export, char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i + 1] != '=')
		i++;
	while (str[i])
	{
		(*export)[i] = str[i];
		i++;
	}
	(*export)[i] = '\0';
}

int	ft_export_name(char *str, char **export_name)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	j = -1;
	count = 1;
	*export_name = malloc(ft_strlen(str) + 1);
	if (!(*export_name))
		return (0);
	while (str[++i] && str[i] != '=')
	{
		if (str[i] == '\\' && count == 1)
		{
			(*export_name)[++j] = '\\';
			count = 0;
		}
		if (str[i] == '\\')
			count = 1;
		else
			(*export_name)[++j] = str[i];
	}
	(*export_name)[i] = '\0';
	if (!ft_find_back_s(*export_name))
		return (0);
	ft_add_export_value(export_name, str);
	return (1);
}

char	*assign_export_empty_value(char *export)
{
	int		i;
	char	*new_export;

	i = 0;
	while (export[i] && export[i] != '=')
		i++;
	if (!export[i])
	{
		i = -1;
		new_export = malloc(ft_strlen(export) + 2);
		while (export[++i])
			new_export[i] = export[i];
		export[i++] = '=';
		export[i++] = '\0';
	}
	if (export[i] == '=')
	{
		new_export = malloc(ft_strlen(export) + 1);
		i = -1;
		while (export[++i])
			new_export[i] = export[i];
		new_export[i++] = '\0';
	}
	free(export);
	return (new_export);
}

int	equal_or_nothing(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		return (0);
	return (1);
}

char	*export_and_equal(char *export)
{
	char	*export_equal;
	int		i;

	i = 0;
	export_equal = (char *) malloc(sizeof(char) * (ft_strlen(export) + 1));
	if (!export_equal)
		perror("malloc export_and equal\n");
	while (export[i])
	{
		export_equal[i] = export[i];
		i++;
	}
	export_equal[i] = '\0';
	return (export_equal);
}

char	*export_and_empty(char *export)
{
	char	*export_empty;
	int		i;

	export_empty = malloc(ft_strlen(export) + 1);
	if (!export_empty)
		perror("export and empty\n");
	i = -1;
	while (export[++i])
		export_empty[i] = export[i];
	export_empty[i] = '\0';
	return (export_empty);
}

int	check_after_equal(char *export)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (export[i])
	{
		if (export[i] && (export[i] == '=' && export[i + 1] == '='))
			return (1);
		if ((export[i] != '=' && flag == 1))
			return (1);
		if (export[i] == '=')
			flag = 1;
		i++;
	}
	return (0);
}

int	ft_check_empty_export(char *export)
{
	char	*export_equal;
	char	*export_non_equal;
	int		i;
	int		res;

	i = 0;
	res = 0;
	export_equal = export_and_equal(export);
	export_non_equal = export_and_empty(export);
	if (!equal_or_nothing(export))
	{
		if (!ft_strcmp(export_equal, export))
			res = 1;
	}
	else
	{
		if (!ft_strcmp(export_non_equal, export))
			res = 2;
	}
	free(export_equal);
	free(export_non_equal);
	if (res == 1)
		return (1);
	else if (res == 2)
		return (2);
	return (0);
}

char	*add_equal_null_char(char *export)
{
	char	*new_export;
	int		i;

	i = 0;
	new_export = malloc(ft_strlen(export) + 1);
	if (!new_export)
		return (NULL);
	while (export[i])
	{
		new_export[i] = export[i];
		i++;
	}
	new_export[i++] = '\0';
	free(export);
	return (new_export);
}

char	*add_null(char *export)
{
	char	*new_export;
	int		i;

	i = 0;
	new_export = malloc(ft_strlen(export) + 2);
	if (!new_export)
		return (NULL);
	while (export[i])
	{
		new_export[i] = export[i];
		i++;
	}
	new_export[i++] = '=';
	new_export[i++] = '\0';
	free(export);
	return (new_export);
}

int	value_start_equal(char *export)
{
	int	i;

	i = 0;
	while (export[i] != '=')
		i++;
	if (export[i] && ((export[i] == '=' && export[i + 1] == '\0')
		|| (export[i] == '=' && export[i + 1] == '=')))
		return (1);
	return (0);
}

char	*add_quote_to_value(char *export)
{
	int	i;
	int	j;
	char	*new_export;

	i = -1;
	new_export = malloc(ft_strlen(export) + 4);
	while (export[++i] != '=')
		new_export[i] = export[i];
	j = i;
	new_export[i++] = '=';
	new_export[i++] = '\'';
	while (export[++j])
	{
		new_export[i] = export[j];
		i++;
	}
	new_export[i] = '\'';
	new_export[++i] ='\0';
	free(export);
	return (new_export);
}

void	clean_env_value(char ***new_env)
{
	int	i;

	i = -1;
	while ((*new_env)[++i])
	{
		if (value_start_equal((*new_env)[i]) == 1)
		{
			(*new_env)[i] = add_quote_to_value((*new_env)[i]);
		}
	}
}

void	ft_print_env_ascii_order(char **env)
{
	char	**new_env;
	int		i;
	int		j;
	char	*tmp;
	char	*export_name_i;
	char	*export_name_j;

	i = -1;
	new_env = dup_env_ascii_order(env);
	clean_env_value(&new_env);
	while(new_env[++i])
	{
		j = i;
		while (new_env[++j])
		{
				export_name_i = ft_find_export_name(new_env[i]);
				export_name_j = ft_find_export_name(new_env[j]);
				if (ft_strcmp_ascii_order(export_name_i, export_name_j) > 0)
				{
					tmp = ft_str_dup_env(new_env[i], tmp);
					free(new_env[i]);
					new_env[i] = ft_str_dup_env(new_env[j], new_env[i]);
					free(new_env[j]);
					new_env[j] = ft_str_dup_env(tmp, new_env[j]);
					free(tmp);
				}
				free(export_name_i);
				free(export_name_j);
		}
	}
	print_tab_tab_ascii_order(new_env);
	free_tab_tab(new_env);
}

int ft_realloc_env(char ***env, int size)
{
	char **cp_env;
	int	i;

	cp_env = dup_env(*env);
	free_tab_tab(*env);
	*env = (char **) malloc (sizeof(char *) * (ft_len_tab_tab(cp_env) + size)); // + 1 ?, NULL est deja mit lorsque j'apelle realloc
	if ((*env) == NULL)
		return (ERROR_MALLOC);
	// gestion d'erreur;
	i = 0;
	while (cp_env[i])
	{
		(*env)[i] = ft_str_dup_env(cp_env[i], (*env)[i]);
		i++;
	}
	free_tab_tab(cp_env);
	return (i);
}

// faire de new env un valeur 
int	ft_export2(char ***env, char *export_str)
{
	char	*export = NULL;
	int		i;
	int		empty;


	printf("passe pas\n");
	if (export_str[0] == '=' || !ft_check_export_name(export_str))
	{
		printf("bash: export:= `%s': not a valid identifier\n", export_str);
		return (2);
		// gestion d'erreur
	}
	if (!ft_export_name(export_str, &export) || !ft_is_ascii(export_str[0]))
	{
		
		printf("export:= not valid in this context: %s\n", export);
		free(export);
		return (2);
	}
	if (!check_after_equal(export))
	{
		empty = ft_check_empty_export(export);
		if (empty == 1)
			export = add_equal_null_char(export);
		else if (empty == 2)
			export = add_null(export);
	}
	// chck a faire l'export se fait avec le nom de l'export pas le total
	if (ft_is_export_in_env(*env, export))
	{
		ft_change_export(env, export);
		{
			free(export);
			return (0);
		}
	}
	i = ft_realloc_env(env, 1);
	(*env)[i] = ft_str_dup_env(export, (*env)[i]);
	(*env)[i + 1] = NULL;
	free(export);
	return(0);
	// return ;
}

int	ft_export(char ***env, char **arg, int free)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	if (!arg[1])
	{
		ft_print_env_ascii_order(*env);;
		return (0); // gestion d'erreur
	}
	while (arg[i])
	{
		status = ft_export2(env, arg[i]);
		i++;
	}
	if (free)
		free_tab_tab(arg);
	return (status);
}

// ajouter l'export de plusieur choix possible export a=qwer b=qwer ... (voir sil y a des cas d'erreurs)

// int	main(int ac, char **av, char **envp)
// {
// 	char	**env;

// 	env = dup_env(envp);
// 	if (ac < 2)
// 		return (1);
// 	ft_export(&env, av[1]);
// 	if (!env)
// 		return (0);
// 	print_tab_tab(env);
// 	free_tab_tab(env);
// 	return (0);
// }

//ft_error to do