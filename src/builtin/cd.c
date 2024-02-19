/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:42:46 by lgarfi            #+#    #+#             */
/*   Updated: 2024/02/19 19:29:02 by lgarfi           ###   ########.fr       */
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
// err de parising $? = 2
void	ft_cd(char **path_tab, char ***env)
{
	char	current_path[PATH_MAX + 1];
	char	new_path[PATH_MAX + 1];
	int		len_path_tab;
	char	*oldpwd;

	// si la taille du chemin est supp a 256 alors le cd ne se fait pas $? = 1
	
	if (getcwd(current_path, PATH_MAX) == NULL)
	{
		printf("Error (%d): %s\n", errno, strerror(errno));
		// gestion
	}
	printf("current path = %s\n", current_path);
	if (!path_tab[1] || ft_strcmp(path_tab[1], "~") == 0) // attention cd et cd ~ ne sont pas identique
	{
		printf("cd vers le home\n");
		if (getcwd(new_path, PATH_MAX) == NULL)
		{
			printf("Error (%d): %s\n", errno, strerror(errno));
			// gestion
		}
		oldpwd = getenv("HOME");
		if (!oldpwd)
		{
			printf("Error OLDPWD does not exist\n"); // a tester et a verfier ce cas
			g_exit_status = 2;
			return ;
		}
		if (chdir(oldpwd) != 0)
		{
			printf("2\n");
			free(oldpwd);
			printf("Error (%d): %s\n", errno, strerror(errno));
			g_exit_status = 2;
			return ;
		}
		printf("1\n");
		ft_change_PWD_OLD_PWD(current_path, new_path, env);
		return ;
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
		oldpwd = getenv("OLDPWD");
		if (!oldpwd)
		{
			printf("Error OLDPWD does not exist\n"); // a tester et a verfier ce cas
			g_exit_status = 2;
			return ;
		}
		if (chdir(oldpwd) != 0)
		{
			free(oldpwd);
			printf("Error (%d): %s\n", errno, strerror(errno));
			g_exit_status = 2;
			return ;
		}
		if (getcwd(new_path, PATH_MAX) == NULL)
		{
			printf("Error (%d): %s\n", errno, strerror(errno));
			free (oldpwd);
			// gestion
		}
		printf("new path = %s\n", new_path);
		ft_change_PWD_OLD_PWD(current_path, new_path, env);
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

// int	main(int ac, char **av, char **envp)
// {
// 	char **env = NULL;

// 	if (ac < 1 || !envp || !av)
// 		return (0);
// 	env = dup_env(envp);
// 	ft_cd(av, &env);
// 	free_tab_tab(env);
// }

// cd restera a tester dans un mini shell car la chdir n'est pas visible ainsi

// fonction similaire (ft_is_export_name_in_env) (ft_find_export_name)