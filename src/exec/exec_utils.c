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
	if (read != 0)
	{
		dup2(read, STDIN_FILENO);
		close(read);
	}
	dup2(write, STDOUT_FILENO);
	if (write > 1)
		close(write);
}

void	exec_cmd(t_minishell *shell, t_exec *exec)
{
	char	*path;

	if (exec->cmd == NULL)
		free_exec_node(&exec);
	path = find_path(shell, exec->cmd);
	if (path == NULL)
		free_exec_node(&exec);
	if (!ft_strncmp(exec->cmd, "exit", 4))
	{
		exit(0);
		free_exec_node(&exec);
	}
	execve(path, exec->args, shell->env);
	perror("Error excecuting execve\n");
	free_exec_node(&exec);
}

void	one_cmd(t_minishell *shell)
{
	shell->pid = fork();
	if (shell->pid == -1)
	{
		perror("fork");
		return ;
	}
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
	}
	while (wait(NULL) > 0)
		;
}
