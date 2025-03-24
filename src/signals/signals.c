/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliobreg <aliobreg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:39:57 by aliobreg          #+#    #+#             */
/*   Updated: 2025/03/24 20:48:05 by aliobreg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <sys/ioctl.h>

static void signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);// borra la linea
		ft_printf("\n");
		rl_on_new_line(); //indica a readline que inicie una linea nueva
		rl_redisplay(); //redibuja la linea y la linea vacia
		g_sigint = SIGINT; //1 es el valor que se le asigna a g_pid cuando se presiona ctrl + c
	}
	/*else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();//2 es el valor que se le asigna a g_pid cuando se presiona ctrl + 
	}*/
	/*else if (sig == SIGTERM)
		g_sigint = 3; //3 es el valor que se le asigna a g_pid cuando se presiona ctrl + d*/
}

// static void child_handler(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		ft_printf("\n");
// 		exit(130);
// 	}
// 	/*else if (sig == SIGQUIT)
// 	{
// 		ft_printf("Quit: 3\n");
// 		exit(131);
// 	}*/ //la quito porque se supone que no hace nada en bash
// }

void wait_signal(void)
{
	struct sigaction	struct_c;
	struct sigaction	struct_q;
	
	sigemptyset(&struct_c.sa_mask);
	struct_c.sa_flags = SA_RESTART;
	// if (sig)
		struct_c.sa_handler = signal_handler;
	// else
		struct_q.sa_handler = SIG_IGN;
	sigaction(SIGINT, &struct_c, NULL);
	sigaction(SIGQUIT, &struct_q, NULL);
}

void children_handler(int signal)
{
	rl_on_new_line();
	if (signal == SIGINT)
		ft_printf("\n");
	else if (signal == SIGQUIT)
		printf("Quit (core dumped)\n");	
	g_sigint = signal;
	
}
void children_signal(void)
{
	struct sigaction	struct_c;
	
	sigemptyset(&struct_c.sa_mask);
	struct_c.sa_flags = SA_RESTART;
	// if (sig)
		struct_c.sa_handler = children_handler;
	// else
	sigaction(SIGINT, &struct_c, NULL);
	sigaction(SIGQUIT, &struct_c, NULL);
}
void other_handler(int signal)
{
	rl_on_new_line();
	ioctl(0, TIOCSTI, "\n");
	g_sigint = signal;
	
}

void other_signals(void)
{
	struct sigaction	struct_c;
	
	sigemptyset(&struct_c.sa_mask);
	struct_c.sa_flags = SA_RESTART;
	// if (sig)
		struct_c.sa_handler = other_handler;
	// else
	sigaction(SIGINT, &struct_c, NULL);
	signal(SIGQUIT, SIG_IGN);
}
