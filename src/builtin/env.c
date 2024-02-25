/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 22:28:44 by lgarfi            #+#    #+#             */
/*   Updated: 2024/02/25 20:20:17 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pustr_builtin_env(char *str)
{
	if (write(1, str, ft_strlen(str)) == -1)
	{
		if (errno == ENOSPC)
		{
			ft_putstr_fd("env: write error: ", 2);
			ft_putstr_fd(strerror(errno), 2);
			exit(2);
		}
		exit (124);
	}
	if (write(1, "\n", 1) <= 0)
	{
		if (errno == ENOSPC)
		{
			ft_putstr_fd("env: write error: ", 2);
			ft_putstr_fd(strerror(errno), 2);
			exit(125);
		}
		exit (2);
	}
}

int	ft_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		ft_pustr_builtin_env(env[i]);
	return (0);
}

// int	main(int ac, char **av, char **env)
// {
// 	ac = 2;
// 	(void)av;
// 	ft_env(env);
// }