/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 22:17:53 by lgarfi            #+#    #+#             */
/*   Updated: 2024/01/26 09:43:09 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// echo affiche un retour a la ligne
// echo -n affiche sans le retour a la ligne final

int	ft_echo(char **tab)
{
	int param;
	int	i;

	param = 0;
	if (tab[1] == NULL)
	{
		printf("\n");
		return (0); // gestion d'erreur
	}
	if (ft_strcmp(tab[1], "-n") == 0)
	{
		tab++;
		param = 1;
	}
	i = 0;
	while (tab[++i + 1])
		printf("%s ", tab[i]);
	printf("%s", tab[i]);
	if (param == 0)
		printf("\n");
	return (0);
}

// int	main(int ac, char **av)
// {
// 	ft_echo(av);
// 	return (0);
// }