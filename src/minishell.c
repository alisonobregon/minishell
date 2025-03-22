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

int g_sigint;

void memory_allocated(t_minishell *shell)
{
	shell->args = (char **)ft_calloc(MAX_ARGUMENTS, sizeof(char **));
	shell->status = 0;
	shell->prompt = ft_calloc(1, sizeof(t_prompt));
	shell->exec = NULL;
	if (!shell->prompt)
		return ;
}

char	*get_input(t_minishell *shell)
{
	char	*prompt;
	char	*buf;

	//shell->pwd = get_prompt(shell);
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
	shell->path = ft_split(getenv("PATH"), ':');

	g_sigint = 0;
	wait_signal(1);
	while (1)
	{
		memory_allocated(shell);
		//shell->prompt->str = get_prompt(shell);
		shell->prompt->str = get_input(shell);
		if (!shell->prompt->str)
			continue ;
		add_history(shell->prompt->str);
		add_history_to_file(shell->prompt->str);
		parsing(shell);
		replace_quotes(&shell->exec->args, shell->env, shell->status);
		if (!is_builtin(shell, shell->exec->cmd))
			exec(shell);
		free(shell->prompt->str);// este tener cuidado
		command_list_clear(&(shell->exec));
		//free(shell->prompt->cwd);
		//free(shell->prompt);
	}
	rl_clear_history();
	free_shell(shell);
	return (0);
}
