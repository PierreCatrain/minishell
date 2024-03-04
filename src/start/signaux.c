/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 06:02:52 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/04 12:04:51 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_display_new_prompt(int signal)
{
	(void)signal;
	if (g_exit_status != -100)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

int	ft_set_sig(void)
{
	struct sigaction	s_int;
	struct sigaction	s_quit;

	sigemptyset(&s_int.sa_mask);
	sigemptyset(&s_quit.sa_mask);
	sigaddset(&s_int.sa_mask, SIGINT);
	sigaddset(&s_quit.sa_mask, SIGQUIT);
	s_int.sa_flags = 0;
	s_quit.sa_flags = SA_RESTART;
	s_int.sa_handler = &ft_display_new_prompt;
	s_quit.sa_handler = SIG_IGN;
	if (sigaction(SIGINT, &s_int, NULL) == -1)
	{
		ft_putstr_fd("minishell: error with sigaction\n", 2);
		return (ERROR);
	}
	if (sigaction(SIGQUIT, &s_quit, NULL) == -1)
	{
		ft_putstr_fd("minishell: error with sigaction\n", 2);
		return (ERROR);
	}
	return (SUCCESS);
}