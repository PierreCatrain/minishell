/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 06:02:52 by picatrai          #+#    #+#             */
/*   Updated: 2024/02/12 07:31:55 by picatrai         ###   ########.fr       */
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
}

void ft_test(int sig)
{
    (void)sig;
    printf("test\n");
}

int ft_set_sig(void)
{
    struct sigaction s_int;
    struct sigaction s_quit;
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
	// signal(3, &sig_quit);
    return (SUCCESS);
}