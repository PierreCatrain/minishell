/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:42:46 by lgarfi            #+#    #+#             */
/*   Updated: 2024/02/09 16:09:50 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char	*ft_str_join_export_name_with_equal_value(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*new_export;

	i = -1;
	new_export = (char *) malloc (ft_strlen(s1) + ft_strlen(s2) + 1);
	while (s1[++i])
		new_export[i] = s1[i];
	j = -1;
	while (s2[++j])
		new_export[++i] = s2[j];
	new_export[i] = '\0';
	free(s1);
	free(s2);
	return (new_export);
}

char	**ft_change_OLD_PWD(char **path_tab, char **env)
{
	char	*export_name = NULL;
	char	*export_value = NULL;
	char	*export_str = NULL;
	char	**new_env = NULL;

	
	export_name = ft_str_dup_env("OLDPWD=", export_name);
	export_value = ft_str_dup_env(getcwd(path_tab[0], 1024), export_value);
	export_str = ft_str_join_export_name_with_equal_value(export_name, export_value);
	new_env = ft_export(env, export_str);
	free(export_str);
	return (new_env);
}

int	is_pwd_in_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strcmp(ft_find_export_name(env[i]), "PWD") == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	ft_pwd_name(char **export_name)
{
	*export_name[0] = 'P';
	*export_name[1] = 'W';
	*export_name[2] = 'D';
	*export_name[3] = '\0';
}

char	**ft_change_PWD(char **env)
{
	char	**new_env;
	char	*export_name;
	int		i;
	int		pwd_index;
	char	buff[PATH_MAX + 1];
	

	new_env = (char **) malloc(sizeof(char *) * (ft_len_tab_tab(env) + 1));
	export_name = malloc (4);
	if (!new_env || !export_name)
	{
		if (new_env)
			free_tab_tab (new_env);
		return (0);
	}
	ft_pwd_name(&export_name);
	pwd_index = is_pwd_in_env(new_env);
	i = -1;
	while (env[++i] && i < pwd_index)
		new_env[i] =  ft_str_dup_env(env[i], new_env[i]);
	new_env[i] =  ft_str_dup_env(getcwd(buff, PATH_MAX), new_env[i]);
	while (env[++i])
		ft_str_dup_env(env[i], new_env[i]);
	new_env[i] = NULL;
	// free (old env) ?
	return (new_env);
}

// int	ft_parsing(char **tab)
// {
// 	int	i;

// 	i = 0;
// 	while (tab[i])
// 	{
// 		i++;
// 	}r    *export_name;
// // }

char	**ft_chang_env_path_and_old_path(char **path_tab, char **env)
{
	char	**new_env;
	
	new_env = ft_change_OLD_PWD(path_tab, env);
	if (is_pwd_in_env(env) != -1)
		new_env = ft_change_PWD(new_env);
	// free old env ?
	return (new_env);
}

// trouver le moyen de changer le old path et le path et de faire un cd que ca marche ou non
char	**ft_cd(char **path_tab, char **env)
{
	char	current_path[PATH_MAX + 1];
	int		len_path_tab;

	printf("affichage de tab de tab\n");
	print_tab_tab(path_tab);
	if (getcwd(current_path, PATH_MAX) != NULL)
	{
		printf("Error (%d): %s\n", errno, strerror(errno));
		// gestion
	}
	if (!path_tab[1] || ft_strcmp(path_tab[1], "~") == 0 || ft_strcmp(path_tab[1], "~") == 0)
	{
			printf("cd vers le home\n");
			//
			return (ft_chang_env_path_and_old_path(path_tab, env));
	}
	len_path_tab = ft_len_tab_tab(path_tab);
	if (len_path_tab > 2)
	{
		printf("bash: cd: too many arguments\n");
		g_exit_status = 1;
		return (NULL);
		// gestion d'erreur
	}
	// free ancien env;
	// faire de new_env une variable de structure et return le bon status
	if (ft_strcmp(path_tab[1], "-"))
	{
		printf("cd vers le OLD PWD\n");
	}
	if (chdir(path_tab[1]) != 0)
	{
		printf("Erreur (%d): %s\n", errno, strerror(errno));
		g_exit_status = 1;
		return (NULL);
		// gestion d'erreur
	}
	return (ft_chang_env_path_and_old_path(path_tab, env));
}

// int	main(int ac, char **av, char **env)
// {
// 	if (ac < 1)
// 		return (0);
// 	ft_cd(av, env);
// 	// av += 1;
// 	// printf("av = \n");
// 	// printf("av[0] = %s\n", av[0]);
// 	// printf("av[1] = %s\n", av[1]);
// 	// printf("av[2] = %s\n", av[2]);
	
// 	// print_tab_tab(av);
// }
 
 // cd restera a tester dans un mini shell car la chdir n'est pas visible ainsi