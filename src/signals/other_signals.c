/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliobreg <aliobreg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 20:24:08 by aliobreg          #+#    #+#             */
/*   Updated: 2025/04/08 20:25:31 by aliobreg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <sys/ioctl.h>

void	other_handler(int signal)
{
	rl_on_new_line();
	ioctl(0, TIOCSTI, "\n");
	g_sigint = signal;
}

void	other_signals(void)
{
	struct sigaction	struct_c;

	sigemptyset(&struct_c.sa_mask);
	struct_c.sa_flags = SA_RESTART;
	struct_c.sa_handler = other_handler;
	sigaction(SIGINT, &struct_c, NULL);
	signal(SIGQUIT, SIG_IGN);
}
