/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:26:44 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/12 08:05:34 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_builtin_err_msg(char *builtin)
{
	char	*builtin_msg;
	char	*err;
	char	*final_msg;

	err = NULL;
	builtin_msg = NULL;
	builtin_msg = ft_str_dup_env(builtin, builtin_msg);
	if (!builtin_msg)
		return (NULL);
	err = ft_str_dup_env(": write error: No space left on device\n", err);
	if (!err)
		return (NULL);
	final_msg = ft_strjoin(builtin_msg, err);
	free(builtin_msg);
	free(err);
	return (final_msg);
}

int	ft_pustr_builtin_pwd(char *str)
{
	char	*err_msg;
	char	*pwd_val;

	pwd_val = ft_strjoin_wihtout_free(str, "\n");
	if (!pwd_val)
		return (ERROR_MALLOC);
	err_msg = ft_get_builtin_err_msg("pwd");
	if (!err_msg)
		return (free(pwd_val), ERROR_MALLOC);
	if (write(1, pwd_val, ft_strlen(pwd_val)) == -1)
	{
		ft_putstr_fd(err_msg, 2);
		return (free(err_msg), free(pwd_val), 1);
	}
	free(pwd_val);
	free(err_msg);
	return (0);
}

int	ft_pwd(char **tab, char **env)
{
	char	*path;
	int		check;

	(void)tab;
	path = ft_get_env_value(env, "PWD");
	if (!path)
		ft_putstr_fd("no path availlable\n", 2);
	check = ft_pustr_builtin_pwd(path);
	free(path);
	return (check);
}
