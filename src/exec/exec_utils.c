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

	/* if (exec->cmd == NULL)
		free_shell(shell); */
	path = find_path(shell, exec->cmd);
	if (path == NULL)
		free_exec_node(&exec);
	execve(path, exec->args, shell->env);
	perror("Error excecuting execve\n");
	free_exec_node(&exec);
}

void	one_cmd(t_minishell *shell)
{
	if (builtin_checker(shell, shell->exec->cmd))
	{
		if (shell->exec->outfile || shell->exec->infile)
		{
			if (!fd_checker(&shell->exec))
				return ;
		}
		if (exec_builtin(shell, shell->exec->cmd) == -1)
			return ;
		multi_dup(shell->exec->stdin, shell->exec->stdout);
	}
	else
	{
		shell->pid = fork();
		if (shell->pid == -1)
			return (perror("fork"));
		if (shell->pid == 0)
		{
			if (shell->exec->outfile || shell->exec->infile)
			{
				if (!fd_checker(&shell->exec))
				return ;
			}
			if (shell->exec->heredoc)
				unlinker(shell->exec->heredoc);
			exec_cmd(shell, shell->exec);
			exit(1);
		}
	}
	while (wait(NULL) > 0)
		;
}
