/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_argc_envp.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 21:27:05 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/03 15:47:25 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_check_argc(int argc, char **argv)
{
	if (argc != 1 && argc != 3)
	{
		ft_putstr_fd("USAGE : ./minishell\n", 2);
		ft_putstr_fd("or\n", 2);
		ft_putstr_fd("USAGE : ./minishell -c \"input\"\n", 2);
		return (ERROR_ARGC_ENVP);
	}
	else if (argc == 3 && ft_strcmp(argv[1], "-c") != 0)
	{
		ft_putstr_fd("USAGE : ./minishell\n", 2);
		ft_putstr_fd("or\n", 2);
		ft_putstr_fd("USAGE : ./minishell -c \"input\"\n", 2);
		return (ERROR_ARGC_ENVP);
	}
	return (SUCCESS);
}
