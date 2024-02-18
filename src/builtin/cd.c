/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:42:46 by lgarfi            #+#    #+#             */
/*   Updated: 2024/02/18 18:35:33 by lgarfi           ###   ########.fr       */
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
		new_export[i++] = s2[j];
	new_export[i] = '\0';
	free(s1);
	free(s2);
	return (new_export);
}

void	ft_change_PWD_OLD_PWD(char *current_path, char *new_path, char ***env)
{
	char	*export_name_old_pwd = NULL;
	char	*export_value_old_pwd = NULL;
	char	*export_str_old_pwd = NULL;
	char	*export_name_new = NULL;
	char	*export_value_new = NULL;
	char	*export_str_new = NULL;
	int		check;

	check = 0;
	if (is_export_name_in_env(*env, "PWD") != -1)
	{
		export_name_new = ft_str_dup_env("PWD=", export_name_new);
		export_value_new = ft_str_dup_env(new_path, export_value_new);
		export_str_new = ft_str_join_export_name_with_equal_value(export_name_new, export_value_new);
		ft_export(env, export_str_new);
		free(export_str_new);
		check = 1;
	}
	if (is_export_name_in_env(*env, "OLDPWD") != 1 || is_export_name_in_env(*env, "OLDPWD"))
	{
		export_name_old_pwd = ft_str_dup_env("OLDPWD=", export_name_old_pwd);
		export_value_old_pwd = ft_str_dup_env(current_path, export_value_old_pwd);
		export_str_old_pwd = ft_str_join_export_name_with_equal_value(export_name_old_pwd, export_value_old_pwd);
		if (check == 1)
		{
			ft_export(env, export_str_old_pwd);
		}
		else
		{
			ft_export(env, export_str_old_pwd);
		}
		free(export_str_old_pwd);
	}
	// free_tab_tab(*env);
	return ;
}

int	is_export_name_in_env(char **env, char *str)
{
	int	i;
	char	*export_name;

	i = 0;

	printf("str = %s\n", str);
	while (env[i])
	{
		export_name = ft_find_export_name(env[i]);
		if (ft_strcmp(export_name, str) == 0)
		{
			free(export_name);
			return (i);
		}
		free(export_name);
		i++;
	}
	return (-1);
}

int	ft_cdpath(char **pathtab)
{
	char	**CDPATH;
	char	**tmp;
	char	*str_CDPATH;

	CDPATH = ft_split(getenv("CDPATH"), ':');
	tmp = CDPATH;
	while(*CDPATH)
	{
		str_CDPATH = ft_strjoin_path(*CDPATH, pathtab[1]);
		if (chdir(str_CDPATH) == 0)
		{
			printf("%s\n", str_CDPATH);
			free(str_CDPATH);
			free_tab_tab(CDPATH);
			return (0);
		}
		free(str_CDPATH);
		CDPATH++;
	}
	free(tmp);
	return (-1);
}

// trouver le moyen de changer le old path et le path et de faire un cd que ca marche ou non
void	ft_cd(char **path_tab, char ***env)
{
	char	current_path[PATH_MAX + 1];
	char	new_path[PATH_MAX + 1];
	int		len_path_tab;

	if (getcwd(current_path, PATH_MAX) == NULL)
	{
		printf("Error (%d): %s\n", errno, strerror(errno));
		// gestion
	}
	if (!path_tab[1] || ft_strcmp(path_tab[1], "~") == 0) // attention cd et cd ~ ne sont pas identique
	{
		printf("cd vers le home\n");
		//
		if (getcwd(new_path, PATH_MAX) == NULL)
		{
			printf("error cwd\n");
			printf("Error (%d): %s\n", errno, strerror(errno));
			// gestion
		}
		ft_change_PWD_OLD_PWD(current_path, new_path, env);
	}
	len_path_tab = ft_len_tab_tab(path_tab);
	if (len_path_tab > 2)
	{
		printf("bash: cd: too many arguments\n");
		g_exit_status = 1;
		return ;
		// gestion d'erreur
	}
	// free ancien env;
	// faire de new_env une variable de structure et return le bon status
	if (ft_strcmp(path_tab[1], "-") == 0)
	{
		printf("cd vers le OLD PWD\n");
		g_exit_status = 0; // si sucess du cd sinon 1 (mssg d'err) = bash: cd: OLDPWD not set
		return ;
	}
	// tester avec cdpath si cd path existe (fonction comme le test avec access)
	if (is_export_name_in_env(*env, "CDPATH") != -1)
	{
		printf("1\n");
		if (ft_cdpath(path_tab) == 0)
		{
			if (getcwd(new_path, PATH_MAX) != NULL)
				ft_change_PWD_OLD_PWD(current_path, new_path, env);
		printf("2\n");
		}
	}
	if (chdir(path_tab[1]) != 0)
	{
		printf("Erreur (%d): %s\n", errno, strerror(errno));
		g_exit_status = 1;
		return ;
		// gestion d'erreur
	}
	if (getcwd(new_path, PATH_MAX) == NULL)
	{
		printf("Error (%d): %s\n", errno, strerror(errno));
		// gestion
	}
	g_exit_status = 0;
	printf("new path = %s\n", new_path);
	ft_change_PWD_OLD_PWD(current_path, new_path, env);
}

// sur les return de cd, il faut return le nouvelle env avec pwd et old pwd modifie

// int	main(int ac, char **av, char **env)
// {
// 	char **res = NULL;
// 	char **new_env;

// 	if (ac < 1)
// 		return (0);
// 	if (!env || !av) {return (1);}
// 	new_env = dup_env(env);
// 	res = ft_cd(av, new_env);
// 	print_tab_tab(res);
// 	// free_tab_tab(new_env);
// 	free_tab_tab(res);
// }

// cd restera a tester dans un mini shell car la chdir n'est pas visible ainsi

// fonction similaire (ft_is_export_name_in_env) (ft_find_export_name)