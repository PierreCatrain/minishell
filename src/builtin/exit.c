/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 21:52:06 by lgarfi            #+#    #+#             */
/*   Updated: 2024/02/23 14:44:23 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

enum bool	ft_atoi(char *str, long long int *res)
{
	int	i;
	int	s;

	i = 0;
	*res = 0;
	s = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (__LONG_LONG_MAX__ / 10 < *res || (*res == __LONG_LONG_MAX__ / 10
				&& str[i] - 48 > __LONG_LONG_MAX__ % 10))
			return (FALSE);
		*res = *res * 10 + str[i] - 48;
		i++;
	}
	*res = s * *res % 256;
	return (TRUE);
}

int	ft_check_exit_char(char *str)
{
	int	i;
	int	flag;
	int	flag_space;

	i = 0;
	flag = 0;
	flag_space = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
	{
		flag_space++;
		i++;
	}
	while (str[i])
	{
		if (str[i] == '+' || str[i] == '-')
			flag++;
		if (((str[i] < '0' || str[i] > '9') && (str[i] != '+'
					&& str[i] != '-')) || ((flag_space > 0 || i >= 1)
				&& (str[i] == '+' || str[i] == '-')))
			return (0);
		i++;
	}
	if (flag > 1)
		return (0);
	return (1);
}

int	ft_exit_parsing(char **arg, long long int *exit_value)
{
	if (arg[2] != NULL)
	{
		printf("bash: exit: too many arguments\n");
		*exit_value = 2;
		return (0);
	}
	return (1);
}

int	ft_exit(char **arg)
{
	long long int	exit_value;

	if (arg[1] == NULL)
		exit (0);
	if (!ft_exit_parsing(arg, &exit_value))
		exit_value = 2;
	else if (ft_atoi(arg[1], &exit_value) == FALSE)
	{
		printf("bash: exit: %s: numeric argument required\n", arg[1]);
		exit(2);
	}
	else if (!ft_check_exit_char(arg[1]))
	{
		printf("bash: exit: %s: numeric argument required\n", arg[1]);
			exit_value = 2;
	}
	free_tab_tab(arg);
	exit(exit_value);
}
