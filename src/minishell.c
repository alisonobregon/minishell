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

void	raise_shell_lvl(t_minishell *shell, char **env)
{
	int		i;
	char	*str;

	i = 0;
	if (!str_in_array(env, "SHLVL="))
	{
		printf("SHLVL not found\n");
		shell->env = add_str_to_array(shell->env, "SHLVL=1");
		return ;
	}
	while (env[i])
	{
		if (ft_strnstr(env[i], "SHLVL=", 6))
		{
			str = ft_itoa(ft_atoi(env[i] + 6) + 1);
			free(shell->env[i]);
			shell->env[i] = ft_str2join("SHLVL=", str, 0, 1);
			break ;
		}
		i++;
	}
	return ;
}

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
	shell = ft_calloc(1, sizeof(t_minishell));
	if (env)
	{
		shell->env = strarray_copy(env);
		shell->path = ft_split(getenv("PATH"), ':');
		(print_shell(), raise_shell_lvl(shell, env));
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
