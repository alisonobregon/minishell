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
	return(buf);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_minishell	*shell;

	print_shell();
	shell = ft_calloc(1, sizeof(t_minishell));
	shell->env = strarray_copy(env);
	if (env)
		shell->path = ft_split(getenv("PATH"), ':');
	shell->status = 0;
	wait_signal();
	while (1)
	{
		memory_allocated(shell);
		g_sigint = 0;
		shell->prompt->str = get_input(shell);
		if (!shell->prompt->str)
			continue ;
		add_history(shell->prompt->str);
		add_history_to_file(shell->prompt->str);
		/* if (!check_prompt_str(shell))
			continue; */
		parsing(shell);
		if (!shell->exec || !shell->exec->cmd)
		{
			round_frees(&shell);
			continue ;
		}
		replace_quotes(&shell->exec->args, shell->env, shell->status);
		exec(shell);
		round_frees(&shell);
	}
	rl_clear_history();
	free_child_shell(&shell);
	return (0);
}
