/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliobreg <aliobreg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:39:57 by aliobreg          #+#    #+#             */
/*   Updated: 2025/03/15 19:06:34 by aliobreg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);// borra la linea
		ft_printf("\n");
		rl_on_new_line(); //indica a readline que inicie una linea nueva
		rl_redisplay(); //redibuja la linea y la linea vacia
		g_sigint = 1; //1 es el valor que se le asigna a g_pid cuando se presiona ctrl + c
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		g_sigint = 2; //2 es el valor que se le asigna a g_pid cuando se presiona ctrl + 
	}
	return ;
	/*else if (sig == SIGTERM)
		g_sigint = 3; //3 es el valor que se le asigna a g_pid cuando se presiona ctrl + d*/
}

static void child_handler(int sig)
{
	if (sig == SIGINT)
		g_sigint = 130;
	else if (sig == SIGQUIT)
	{
		ft_printf("Quit: 3\n");
		g_sigint = 131;
	}
	/*else if (sig == SIGTERM)
		g_sigint = 3;*/
	return ;
}

void wait_signal(int sig)
{
	struct sigaction	struct_s;
	
	if (sig)
		struct_s.sa_handler = signal_handler;
	else
		struct_s.sa_handler = child_handler;
	sigemptyset(&struct_s.sa_mask);
	struct_s.sa_flags = SA_RESTART;
	sigaction(SIGINT, &struct_s, NULL);
	sigaction(SIGQUIT, &struct_s, NULL);
	sigaction(SIGTERM, &struct_s, NULL);
}
