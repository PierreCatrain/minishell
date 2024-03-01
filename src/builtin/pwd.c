/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:26:44 by lgarfi            #+#    #+#             */
/*   Updated: 2024/02/29 16:25:43 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char	*ft_get_builtin_err_msg(char *builtin)
{
	char	*builtin_msg;
	char	*error_msg;
	char	*final_msg;

	error_msg = NULL;
	builtin_msg = NULL;
	builtin_msg = ft_str_dup_env(builtin, builtin_msg);
	if (!builtin_msg)
		return (NULL);
	error_msg = ft_str_dup_env(": write error: No space left on device\n", error_msg);
	if (!error_msg)
		return (NULL);
	final_msg = ft_strjoin(builtin_msg, error_msg);
	free(builtin_msg);
	free(error_msg);
	return (final_msg);
}

void	ft_pustr_builtin_pwd(char *str)
{
	char	*err_msg;

	err_msg = ft_get_builtin_err_msg("pwd");	
	if (write(1, str, ft_strlen(str)) == -1)
	{
		if (errno == ENOSPC)
		{
			ft_putstr_fd(err_msg, 2);
			ft_putstr_fd(strerror(errno), 2);
			free(err_msg);
			exit(125);
		}
		exit(0);
	}
	if (write(1, "\n", 1) == -1)
	{
		if (errno == ENOSPC)
		{
			ft_putstr_fd(err_msg, 2);
			ft_putstr_fd(strerror(errno), 2);
			free(err_msg);
			exit(125);
		}
		exit (0);
	}
	free(err_msg);
}

// gerer correment les parametres s'il y en a
int	ft_pwd(char **tab)
{
	char	buff[PATH_MAX + 1];
	(void)tab;
	if (getcwd(buff, PATH_MAX) == NULL)
	{
		ft_msg_err_getcwd();
		return (2);
	}
	ft_pustr_builtin_pwd(buff);
	return (0);
}

// int	main(int ac, char **av)
// {
// 	(void)ac;
// 	ft_pwd(av);
// }