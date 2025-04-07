/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:45:33 by marvin            #+#    #+#             */
/*   Updated: 2025/03/01 17:45:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	len_pipes(t_exec *exec)
{
	int	len;

	len = 0;
	while (exec)
	{
		if (exec->todo_next == 2)
			len++;
		if (exec->next == NULL)
			break ;
		exec = exec->next;
	}
	return (len);
}

void	multi_dup(int read, int write)
{
	dup2(read, STDIN_FILENO);
	if (read != 0)
		close(read);
	dup2(write, STDOUT_FILENO);
	if (write > 1)
		close(write);
}

void	exec_cmd(t_minishell *shell, t_exec *exec)
{
	char	*path;

	if (check_binary(shell, exec, exec->cmd) == -1)
	{
		shell->status = 127;
		free_child_shell(&shell);
		exit(127);
	}
	path = find_path(shell, exec->cmd);
	if (path == NULL)
	{
		(ft_putstr_fd(exec->cmd, 2), ft_putstr_fd(": command not found\n", 2));
		(free_child_shell(&shell));
		exit(127);
	}
	execve(path, exec->args, shell->env);
	perror("Error excecuting execve\n");
	free(path);
	free_child_shell(&shell);
	signal(SIGQUIT, SIG_IGN);
	exit(127);
}

int	exec_a_builting(t_minishell *shell, t_exec *exec)
{
	if (exec->outfile || exec->infile)
	{
		exec->stdin = dup(STDIN_FILENO);
		exec->stdout = dup(STDOUT_FILENO);
		if (!fd_checker(&exec))
		{
			shell->status = 1;
			return (shell->status);
		}
	}
	if (exec_builtin(shell, exec->cmd, exec->args) == -1)
	{
		shell->status = 127;
		return (shell->status);
	}
	return (multi_dup(exec->stdin, exec->stdout), shell->status);
}

int	one_cmd(t_minishell *shell)
{
	children_signal();
	if (builtin_checker(shell, shell->exec->cmd))
	{
		return (exec_a_builting(shell, shell->exec));
	}
	else
	{
		shell->pid = fork();
		if (shell->pid == -1)
		{
			shell->status = 100;
			return (perror("fork"), shell->status);
		}
		if (shell->pid == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			if (shell->exec->outfile || shell->exec->infile)
			{
				if (!fd_checker(&shell->exec))
				{
					shell->status = 1;
					return (-1);
				}
			}
			if (shell->exec->heredoc)
				unlinker(shell->exec->heredoc);
			exec_cmd(shell, shell->exec);
		}
	}
	return (one_cmd_waiter(shell));
}
