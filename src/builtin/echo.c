/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 22:17:53 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/02 14:33:46 by lgarfi           ###   ########.fr       */
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
	ft_echo2(tab, i, param);
	return (0);
}

// int	main(int ac, char **av)
// {
// 	(void)ac;
// 	ft_echo(av);
// 	return (0);
// }