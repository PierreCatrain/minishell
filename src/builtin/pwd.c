/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:26:44 by lgarfi            #+#    #+#             */
/*   Updated: 2024/01/29 07:53:26 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

// gerer correment les parametres s'il y en a
void	ft_pwd(char **tab)
{
	char	buff[PATH_MAX + 1];

	if (getcwd(buff, PATH_MAX) != NULL)
		printf("la %s\n", buff);
	else
		printf("Error (%d): %s\n", errno, strerror(errno));
	free_tab_tab(tab);
}