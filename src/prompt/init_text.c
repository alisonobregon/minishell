#include "../../include/minishell.h"

int print_shell(void)
{
    printf(GREEN BOLD "        ████████╗██╗  ██╗███████╗    ██╗      █████╗ ████████╗ █████╗ ███╗   ███╗     ██████╗██╗  ██╗███████╗██╗     ██╗\n" DEFAULT);
    printf(GREEN BOLD "        ╚══██╔══╝██║  ██║██╔════╝    ██║     ██╔══██╗╚══██╔══╝██╔══██╗████╗ ████║    ██╔════╝██║  ██║██╔════╝██║     ██║\n" DEFAULT);
    printf(GREEN BOLD "           ██║   ███████║█████╗      ██║     ███████║   ██║   ███████║██╔████╔██║    ███████╗███████║█████╗  ██║     ██║\n" DEFAULT);
    printf(GREEN BOLD "           ██║   ██╔══██║██╔══╝      ██║     ██╔══██║   ██║   ██╔══██║██║╚██╔╝██║    ╚════██║██╔══██║██╔══╝  ██║     ██║\n" DEFAULT);
    printf(GREEN BOLD "           ██║   ██║  ██║███████╗    ███████╗██║  ██║   ██║   ██║  ██║██║ ╚═╝ ██║    ███████║██║  ██║███████╗███████╗███████╗\n" DEFAULT);
    printf(GREEN BOLD "           ╚═╝   ╚═╝  ╚═╝╚══════╝    ╚══════╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝╚═╝     ╚═╝    ╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n\n" DEFAULT);

    printf(YELLOW BOLD "                           ▄███████████▄\n" DEFAULT);
    printf(YELLOW BOLD "                           ████▀▀▀▀▀████\n" DEFAULT);
    printf(YELLOW BOLD "                           ████      ████   " CYAN BOLD "🌎 Welcome to The LATAM Shell 🌎\n" DEFAULT);
    printf(YELLOW BOLD "                           ████  ▀  ▀████   " BLUE BOLD "🚀 Fast. 🔥 Powerful. 🛠️ Built for Hackers. \n" DEFAULT);
    printf(YELLOW BOLD "                           ▀████▄███▄████▀\n" DEFAULT);
    printf(YELLOW BOLD "                            ███████████\n" DEFAULT);
    printf(YELLOW BOLD "                             ██ ███ ██\n" DEFAULT);
    
    printf(CYAN BOLD "\n💻  Type your command below...\n\n" DEFAULT);
    printf(RED BOLD "➜ " DEFAULT WHITE);
    
    
	return (0);
}