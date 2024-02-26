/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 06:02:52 by picatrai          #+#    #+#             */
/*   Updated: 2024/02/26 03:29:07 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void ft_display_new_prompt(int signal)
{
    (void)signal;
    write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_exit_status = 130;
}

int ft_set_sig(void)
{
    struct sigaction s_int;
    struct sigaction s_quit;

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