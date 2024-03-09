/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 22:17:53 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/09 22:34:52 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo_2_1(char **tab, int *i)
{
	char	*echo_val;

	if (tab[2] != NULL)
	{
		while (tab[(*i) + 1])
		{
			echo_val = ft_strjoin_wihtout_free(tab[(*i)], " ");
			if (!echo_val)
				return (ERROR_MALLOC);
			if (write (1, echo_val, ft_strlen(echo_val)) == -1)
			{
				ft_putstr_fd("echo: write error: ", 2);
				ft_putstr_fd(strerror(errno), 2);
				ft_putstr_fd("\n", 2);
				free(echo_val);
				return (1);
			}
			free(echo_val);
			(*i)++;
		}
	}
	return (0);
}

int	ft_echo2(char **tab, int i, int param)
{
	if (ft_echo_2_1(tab, &i) == 1)
		return (1);
	if (tab[2] == NULL && ft_strcmp(tab[1], "-n") == 0)
		return (0);
	if (write(1, tab[i], ft_strlen(tab[i])) == -1)
	{
		ft_putstr_fd("echo: write error: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	if (param == 0)
	{
		if (write(1, "\n", 1) == -1)
		{
			ft_putstr_fd("echo: write error: ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			return (1);
		}
	}
	return (0);
}

int	ft_echo(char **tab)
{
	int	param;
	int	i;
	int	check;

	param = 0;
	i = 1;
	if (tab[1] == NULL)
	{
		printf("\n");
		return (0);
	}
	if (ft_strcmp(tab[1], "-n") == 0)
	{
		i = 2;
		param = 1;
	}
	check = ft_echo2(tab, i, param);
	return (check);
}
