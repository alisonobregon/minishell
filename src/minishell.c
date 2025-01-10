/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 22:05:14 by gongarci          #+#    #+#             */
/*   Updated: 2025/01/09 22:06:22 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* Aqui vamos a crear el while loop principal
	*/

void	print_header()
{
ft_printf("  _      _        _                         \n");
ft_printf(" | |    (_)      | |                        \n");
ft_printf(" | |     _  ___  | |_   ___  _ __  ___  ___ \n");
ft_printf(" | |    | |/ _ \\ | __| / _ \\| '__|/ _ \\/ __|\n");
ft_printf(" | |____| |  __/ | |_ |  __/| |  |  __/\\__ \\\n");
ft_printf(" |______|_|\\___|  \\__| \\___||_|   \\___||___/\n");
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	*shell;

	shell = ft_calloc(1, sizeof(t_minishell));
	if (!shell)
		return (1);
	(void)argc;
	(void)argv;
	shell->env = env;
	/* if (getenv("PATH") == NULL)
	{
		 buscar path find_path y asignar o de lo contrario
		return 
	} */
	shell->path = ft_split(getenv("PATH"), ':');
	if (!shell->path)
		return (1); // free shell
	while(1)
	{
		print_header();
		// Print prompt
		shell->prompt->line = get_next_line(0);
		
		if (!shell->prompt->line)
			break ;
		printf("prompt: %s\n", shell->prompt->line);
		// Read command
		// Parse command
		// Execute command
		// Print output
	}
	return (0);
}
