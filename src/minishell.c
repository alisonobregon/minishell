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

void memory_allocated(t_minishell *shell)
{
	shell->prompt = ft_calloc(1, sizeof(t_prompt));
	shell->args = ft_calloc(1, sizeof(char *));
	shell->path = NULL;
	if (!shell->prompt)
		return ;
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_minishell	*shell;

	shell = ft_calloc(1, sizeof(t_minishell));
	if (!shell)
		return (1);
	shell->env = strarray_copy(env); 
	memory_allocated(shell);
	shell->path = ft_split(getenv("PATH"), ':');
	if (!shell->path)
		shell->path[0] = ft_strdup("./") ; // why ? maybe in none env case
	//ft_printf("\033[1;1H\033[2J");//revisar 
	//shell->cwd_int = 0;
	while (1)
	{
		//if (shell->cwd_int == 0)
		shell->cwd = get_prompt(shell);
		shell->prompt->str = readline(shell->cwd);
		add_history(shell->prompt->str);
		add_history_to_file(shell->prompt->str);
		parsing(shell);
		print_command_list(shell->exec);
		if (!is_builtin(shell, shell->exec->cmd))
			exec(shell);
	}
	rl_clear_history();
	return (0);
}
