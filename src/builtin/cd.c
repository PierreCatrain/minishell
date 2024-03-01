/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:42:46 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/01 14:20:11 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

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
		ft_export2(env, export_str_new);
		free(export_str_new);
		check = 1;
	}
	if (is_export_name_in_env(*env, "OLDPWD") != 1 || is_export_name_in_env(*env, "OLDPWD"))
	{
		export_name_old_pwd = ft_str_dup_env("OLDPWD=", export_name_old_pwd);
		export_value_old_pwd = ft_str_dup_env(current_path, export_value_old_pwd);
		export_str_old_pwd = ft_str_join_export_name_with_equal_value(export_name_old_pwd, export_value_old_pwd);
		if (check == 1)
			ft_export2(env, export_str_old_pwd);
		else
			ft_export2(env, export_str_old_pwd);
		free(export_str_old_pwd);
	}
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
		str_CDPATH = ft_strjoin_path_without_free(*CDPATH, pathtab[1]);
		if (chdir(str_CDPATH) == 0)
		{
			printf("%s\n", str_CDPATH);
			free(str_CDPATH);
			free_tab_tab(tmp);
			return (0);
		}
		free(str_CDPATH);
		CDPATH++;
	}
	free(tmp);
	return (-1);
}

// bash: cd: toto: No such file or directory

int	ft_msg_err_chdir(char *str)
{
	char	*first_part;
	char	*second_part;
	char	*err_msg;

	first_part = ft_strjoin_wihtout_free("bash: cd: ", str);
	if (!first_part)
		return (ERROR_MALLOC);
	second_part = ft_strjoin_wihtout_free(": No such", " file or directory\n");
	if (!first_part)
		return (ERROR_MALLOC);
	err_msg = ft_strjoin_wihtout_free(first_part, second_part);
	if (!first_part)
		return (ERROR_MALLOC);
	ft_putstr_fd(err_msg, 2);
	free(first_part);
	free(second_part);
	free(err_msg);
	return (0);
}

void	ft_msg_err_getcwd(void)
{
	ft_putstr_fd("sh: 0 : getcwd() failed: No such file or directory\n", 2);
}

int	ft_cd(char **path_tab, char ***env)
{
	char	current_path[PATH_MAX + 1];
	char	new_path[PATH_MAX + 1];
	int		len_path_tab;
	char	*oldpwd;

	// si la taille du chemin est supp a 256 alors le cd ne se fait pas $? = 1
	printf("1\n");
	if (getcwd(current_path, PATH_MAX) == NULL)
	{
		printf("dans 1\n");
		ft_msg_err_getcwd();
		return (2);
		// gestion
	}
	printf("2\n");
	if (!path_tab[1] || ft_strcmp(path_tab[1], "~") == 0) // attention cd et cd ~ ne sont pas identique
	{
		printf("dans 2\n");
		oldpwd = getenv("HOME");
		if (!oldpwd)
		{
			ft_putstr_fd("bash: cd: HOME not set\n", 2); // a tester et a verfier ce cas
			return (2);
		}
		if (chdir(oldpwd) != 0)
		{
			ft_msg_err_chdir(oldpwd);
			free(oldpwd);
			return (1);
		}
		if (getcwd(new_path, PATH_MAX) == NULL)
		{
			ft_msg_err_getcwd();
			free(oldpwd);
			return (1);
			// gestion
		}
		ft_change_PWD_OLD_PWD(current_path, new_path, env);
		return (0);
	}
	len_path_tab = ft_len_tab_tab(path_tab);
	printf("3\n");
	if (len_path_tab > 2)
	{
		printf("dans 3\n");
		ft_putstr_fd("bash: cd: too many arguments\n", 2);
		return (1);
		// gestion d'erreur
	}
	printf("4\n");
	if (ft_strcmp(path_tab[1], "-") == 0)
	{
		printf("dans 4\n");
		oldpwd = getenv("OLDPWD");
		if (!oldpwd)
		{
			ft_putstr_fd("bash: cd: OLDPWD not set\n", 2); // a tester et a verfier ce cas
			return (1);
		}
		if (chdir(oldpwd) != 0)
		{
			if (ft_msg_err_chdir(oldpwd) == ERROR_MALLOC)
				return (ERROR_MALLOC);// gestion gc
			free(oldpwd);
			return (1);
		}
		if (getcwd(new_path, PATH_MAX) == NULL)
		{
			free (oldpwd);
			ft_msg_err_getcwd();
			return (1);
			// gestion
		}
		printf("%s\n", new_path);
		ft_change_PWD_OLD_PWD(current_path, new_path, env);
		return (0);
	}
	// tester avec cdpath si cd path existe (fonction comme le test avec access)
	printf("5\n");

	if (chdir(path_tab[1]) != 0)
	{
		printf("cd classique ne marche pas\n");
		if (is_export_name_in_env(*env, "CDPATH") != -1)
		{
			printf("CDPATH est dans env\n");
			if (ft_cdpath(path_tab) == 0)
			{
				printf("cdpath a fonctionne\n");
				if (getcwd(new_path, PATH_MAX) != NULL)
				{
					printf("changement de pwd et old pwd\n");
					ft_change_PWD_OLD_PWD(current_path, new_path, env);
					printf("fin du changement\n");
					return (0);
				}
				else
				{
					ft_msg_err_getcwd();
					return (1);
				}
			}
		}
		printf("cd classique ne marche pas j'affiche le mess d'err\n");
		if (ft_msg_err_chdir(path_tab[1]) == ERROR_MALLOC)
			return (ERROR_MALLOC);
		printf("je return 1\n");
		return (1);
		// gestion d'erreur
	}
	printf("7\n");
	printf("je chope new path\n");
	if (getcwd(new_path, PATH_MAX) == NULL)
	{
		ft_msg_err_getcwd();
		return (1);
		// gestion
	}
	printf("8\n");
	printf("je modifie l'env\n");
	ft_change_PWD_OLD_PWD(current_path, new_path, env);
	return (0);
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