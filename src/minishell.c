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

int	g_sigint;

void	memory_allocated(t_minishell *shell)
{
	(void)shell;
	shell->exec = NULL;
	if (!shell->prompt)
		shell->prompt = ft_calloc(1, sizeof(t_prompt));
	g_sigint = 0;
}

char	*get_input(t_minishell *shell)
{
	char	*prompt;
	char	*buf;

	prompt = get_prompt(shell);
	buf = readline(prompt);
	free(prompt);
	if (!buf)
	{
		ft_printf("\n");
		exit(free_shell(shell));
	}
	if (ft_strlen(buf) == 0)
	{
		free(buf);
		return (NULL);
	}
	return (buf);
}

void	execute_command_line(t_minishell *shell)
{
	memory_allocated(shell);
	shell->prompt->str = get_input(shell);
	if (!shell->prompt->str)
		return ;
	add_history(shell->prompt->str);
	add_history_to_file(shell->prompt->str);
	parsing(shell);
	if (!shell->exec || !shell->exec->cmd)
	{
		round_frees(&shell);
		return ;
	}
	replace_quotes(&shell->exec->args, shell->env, shell->status);
	exec(shell);
	round_frees(&shell);
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	*shell;

	(void)argc;
	(void)argv;
	print_shell();
	shell = ft_calloc(1, sizeof(t_minishell));
	if (env)
	{
		shell->env = strarray_copy(env);
		shell->path = ft_split(getenv("PATH"), ':');
	}
	shell->status = 0;
	wait_signal();
	while (1)
	{
		if (g_sigint == 1)
		{
			g_sigint = 0;
			continue ;
		}
		execute_command_line(shell);
	}
	rl_clear_history();
	free_child_shell(&shell);
	return (0);
}
