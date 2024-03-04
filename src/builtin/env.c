/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 22:28:44 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/04 09:34:32 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pustr_builtin_env(char *str)
{
	if (write(1, str, ft_strlen(str)) == -1)
	{
		if (errno == ENOSPC)
		{
			ft_putstr_fd("env: write error: ", 2);
			ft_putstr_fd(strerror(errno), 2);
			return (125);
		}
	}
	if (write(1, "\n", 1) == -1)
	{
		if (errno == ENOSPC)
		{
			ft_putstr_fd("env: write error: ", 2);
			ft_putstr_fd(strerror(errno), 2);
			return (125);
		}
	}
	return (0);
}

int	ft_env(char **env)
{
	int	i;
	int	status;

	i = -1;
	status = 0;
	while (env[++i])
		status = ft_pustr_builtin_env(env[i]);
	return (status);
}

// int	main(int ac, char **av, char **env)
// {
// 	ac = 2;
// 	(void)av;
// 	ft_env(env);
// }