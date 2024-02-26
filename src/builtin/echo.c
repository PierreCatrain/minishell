/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 22:17:53 by lgarfi            #+#    #+#             */
/*   Updated: 2024/02/26 02:43:11 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo2(char **tab, int i, int param)
{
	if (tab[2] != NULL)
	{
		while (tab[i + 1])
		{
			printf("%s ", tab[i]);
			i++;
		}
	}
	if (tab[2] == NULL && ft_strcmp(tab[1], "-n") == 0)
		return ;
	printf("%s", tab[i]);
	if (param == 0)
		printf("\n");
}

int	ft_echo(char **tab)
{
	int	param;
	int	i;

	print_tab_tab(tab);
	param = 0;
	i = 1;
	if (tab[1] == NULL)
	{
		printf("\n");
		//free_tab_tab(tab);
		return (0);
	}
	if (ft_strcmp(tab[1], "-n") == 0)
	{
		i = 2;
		param = 1;
	}
	ft_echo2(tab, i, param);
	// free_tab_tab(tab);
	return (0);
}

// int	main(int ac, char **av)
// {
// 	(void)ac;
// 	ft_echo(av);
// 	return (0);
// }