/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:54:17 by gongarci          #+#    #+#             */
/*   Updated: 2025/03/31 16:17:33 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	header_two(void)
{
	printf(YELLOW BOLD "                           ▄███████████▄\n" DEFAULT);
	printf(YELLOW BOLD "                           ████▀▀▀▀▀████\n" DEFAULT);
	printf(YELLOW BOLD "                           ████      ████   \
	" CYAN BOLD "🌎 Welcome to The LATAM Shell 🌎\n" DEFAULT);
	printf(YELLOW BOLD "                           ████  ▀  ▀████   \
	" BLUE BOLD "🚀 Fast. 🔥 Powerful. 🛠️ Built for Hackers. \n" DEFAULT);
	printf(YELLOW BOLD "                           ▀████▄███▄████▀\n" DEFAULT);
	printf(YELLOW BOLD "                            ███████████\n" DEFAULT);
	printf(YELLOW BOLD "                             ██ ███ ██\n" DEFAULT);
	printf(CYAN BOLD "\n💻  Type your command below...\n\n" DEFAULT);
	printf(RED BOLD "➜ " DEFAULT WHITE);
}

void	print_shell(void)
{
	printf(GREEN BOLD "        ████████╗██╗  ██╗███████╗    ██╗      █████╗ \
████████╗ █████╗ ███╗   ███╗     ██████╗██╗  ██╗███████╗██╗     ██╗\
\n" DEFAULT);
	printf(GREEN BOLD "        ╚══██╔══╝██║  ██║██╔════╝    ██║     ██╔══██╗\
╚══██╔══╝██╔══██╗████╗ ████║    ██╔════╝██║  ██║██╔════╝██║     ██║\
\n" DEFAULT);
	printf(GREEN BOLD "           ██║   ███████║█████╗      ██║     ███████║\
	██║   ███████║██╔████╔██║    ███████╗███████║█████╗  ██║     ██║\
	\n" DEFAULT);
	printf(GREEN BOLD "           ██║   ██╔══██║██╔══╝      ██║     ██╔══██║\
	██║   ██╔══██║██║╚██╔╝██║    ╚════██║██╔══██║██╔══╝  ██║     ██║\
	\n" DEFAULT);
	printf(GREEN BOLD "           ██║   ██║  ██║███████╗    ███████╗██║  ██║\
	██║   ██║  ██║██║ ╚═╝ ██║    ███████║██║  ██║███████╗███████╗███████╗\
	\n" DEFAULT);
	printf(GREEN BOLD "           ╚═╝   ╚═╝  ╚═╝╚══════╝    ╚══════╝╚═╝  ╚═╝\
	╚═╝   ╚═╝  ╚═╝╚═╝     ╚═╝    ╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\
	\n\n"DEFAULT);
	header_two();
}
