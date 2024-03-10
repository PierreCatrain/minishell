/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_shlvl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:10:37 by lgarfi            #+#    #+#             */
/*   Updated: 2024/03/09 22:41:47 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_atoi_int_shlvl_export(char *nb)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	if (nb[0] == '+')
		i++;
	while (nb[i])
	{
		if (nb[i] < '0' || nb[i] > '9')
			return (0);
		i++;
	}
	i = 0;
	while (nb[i])
	{
		if (nb[i] < '0' || nb[i] > '9')
			return (0);
		res = res * 10 + nb[i] - 48;
		i++;
	}
	res -= 1;
	return (res);
}

char	*ft_change_shlvl_export(char *shlvl)
{
	char	*res_val;
	char	*res;

	res_val = ft_itoa_shlvl(ft_atoi_int_shlvl_export(shlvl));
	if (!res_val)
		return (NULL);
	res = ft_strjoin_wihtout_free("SHLVL=", res_val);
	free(res_val);
	return (res);
}
