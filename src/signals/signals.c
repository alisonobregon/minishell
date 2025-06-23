/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliobreg <aliobreg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:39:57 by aliobreg          #+#    #+#             */
/*   Updated: 2025/03/29 18:05:31 by aliobreg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <sys/ioctl.h>

static void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		ft_printf("\n");
		rl_on_new_line();
		rl_redisplay();
		g_sigint = SIGINT;
	}
}

void	wait_signal(void)
{
	struct sigaction	struct_c;
	struct sigaction	struct_q;

	sigemptyset(&struct_c.sa_mask);
	sigemptyset(&struct_q.sa_mask);
	struct_c.sa_flags = SA_RESTART;
	struct_q.sa_flags = SA_RESTART;
	struct_c.sa_handler = signal_handler;
	struct_q.sa_handler = SIG_IGN;
	sigaction(SIGINT, &struct_c, NULL);
	sigaction(SIGQUIT, &struct_q, NULL);
}

void	children_handler(int signal)
{
	rl_on_new_line();
	if (signal == SIGINT)
		ft_printf("\n");
	else if (signal == SIGQUIT)
		printf("Quit (core dumped)\n");
	g_sigint = signal;
}

void	children_signal(void)
{
	struct sigaction	struct_c;

	sigemptyset(&struct_c.sa_mask);
	struct_c.sa_flags = SA_RESTART;
	struct_c.sa_handler = children_handler;
	sigaction(SIGINT, &struct_c, NULL);
	sigaction(SIGQUIT, &struct_c, NULL);
}
