/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 06:02:52 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/22 16:53:49 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_display_new_prompt(int signal)
{
	(void)signal;
	printf("qwer\n");
	if (g_signal != -100 && g_signal != 131)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	g_signal = 130;
}

void	ft_core_dumped(int signal)
{
	(void)signal;
	ft_putstr_fd("Quit (core dumped)\n", 2);
	g_signal = 131;
}

int	ft_change_sig(int index)
{
	struct sigaction	s_quit;
	struct sigaction	s_int;

	sigemptyset(&s_quit.sa_mask);
	sigaddset(&s_quit.sa_mask, SIGQUIT);
	sigemptyset(&s_int.sa_mask);
	sigaddset(&s_int.sa_mask, SIGINT);
	s_int.sa_flags = 0;
	s_quit.sa_flags = 0;
	if (index == 0)
	{
		s_quit.sa_handler = &ft_core_dumped;
		s_int.sa_handler = SIG_IGN;
	}
	else if (index == 1)
	{
		s_quit.sa_handler = SIG_IGN;
		s_int.sa_handler = &ft_display_new_prompt;
	}
	if (sigaction(SIGQUIT, &s_quit, NULL) == -1)
	{
		ft_putstr_fd("minishell: error with sigaction\n", 2);
		return (ERROR);
	}
	if (sigaction(SIGINT, &s_int, NULL) == -1)
	{
		ft_putstr_fd("minishell: error with sigaction\n", 2);
		return (ERROR);
	}
	return (SUCCESS);
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
	s_quit.sa_flags = 0;
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
