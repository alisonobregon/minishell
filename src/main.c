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

int	main(int argc, char **argv)
{
	t_minishell	*shell;

	shell = ft_calloc(1, sizeof(t_minishell));
	if (!shell)
		return (1);
	(void)argc;
	(void)argv;
	ft_printf("Hello, World!\n");
	while(1)
	{
		// Print prompt
		shell->line = get_next_line(0);
		if (!shell->line)
			break ;
		printf("line: %s\n", shell->line);
		free(shell->line);
		// Read command
		// Parse command
		// Execute command
		// Print output
	}
	return (0);
}
