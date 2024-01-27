/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 00:44:25 by lgarfi            #+#    #+#             */
/*   Updated: 2024/01/27 19:05:31 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <limits.h>
#include <linux/limits.h>

// # ====================================================== #
// |														|
// |					PROTOTYPAGE							|
// |														|
// # ====================================================== #

typedef	enum
{
	FALSE = 0,
	TRUE = 1
}		bool;

// # ====================================================== #
// |														|
// |					EXPORT								|
// |														|
// # ====================================================== #

void	free_tab_tab(char **tab);
void	print_tab_tab(char **tab);
void	clean_env_value(char ***new_env);
void	ft_print_env_ascii_order(char **env);
void	print_tab_tab_ascii_order(char **tab);
void	ft_add_export_value(char **export, char *str);
int		ft_is_ascii(char c);
int		ft_strlen(char *str);
int		ft_find_back_s(char *str);
int		ft_len_tab_tab(char **env);
int		equal_or_nothing(char *str);
int		ft_strcmp(char *s1, char *s2);
int		check_after_equal(char *export);
int		value_start_equal(char *export);
int		ft_check_export_name(char *str);
int		ft_check_empty_export(char *export);
int		ft_strcmp_ascii_order(char *s1, char *s2);
int		ft_is_export_in_env(char **env, char *str);
int		ft_strncmp_exec(char *s1, char *s2, size_t size);
int		ft_find_export_index(char **env, char *str);
int		ft_export_name(char *str, char **export_name);
char	*add_null(char *export);
char	*ft_find_export_name(char *str);
char	*export_and_equal(char *export);
char	*export_and_empty(char *export);
char	*add_quote_to_value(char *export);
char	*add_equal_null_char(char *export);
char	*ft_str_dup_env(char *s1, char *s2);
char	*assign_export_empty_value(char *export);
char	**dup_env(char **env);
char	**dup_env_ascii_order(char **env);
char	**ft_change_export(char **env, char *str, char **new_env);

char	**ft_export(char **env, char *export_str);

// # ====================================================== #
// |														|
// |					UNSET								|
// |														|
// # ====================================================== #

int		ft_unset_is_in_env(char **env, char *unset_str);
int		ft_find_unset_index(char **env, char *unset_str);
char	**ft_copy_env_exept_unset(char **env, int unset_index);
char	**ft_unset(char **env, char *unset_str);

// # ====================================================== #
// |														|
// |					  CD								|
// |														|
// # ====================================================== #

char	**ft_cd(char **path_tab, char **env);
char	*ft_str_join_export_name_with_equal_value(char *s1, char *s2);
char	**ft_change_OLD_PWD(char **path_tab, char **env);

// # ====================================================== #
// |														|
// |					ECHO								|
// |														|
// # ====================================================== #

int		ft_echo(char **tab);

// # ====================================================== #
// |														|
// |					  PWD								|
// |														|
// # ====================================================== #

void	ft_pwd(char **tab);

// # ====================================================== #
// |														|
// |					EXIT								|
// |														|
// # ====================================================== #

int	ft_exit(char **arg);

// # ====================================================== #
// |														|
// |					  ENV								|
// |														|
// # ====================================================== #

void	ft_env(char **env);

#endif