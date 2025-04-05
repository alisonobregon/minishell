/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:06:51 by marvin            #+#    #+#             */
/*   Updated: 2025/03/31 12:06:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_cmds(t_minishell *shell, t_exec *exec)
{
	char	*path;

	if (check_binary(shell, exec, exec->cmd) == -1)
	{
		shell->status = 127;
		free_child_shell(&shell);
		return ;
	}
	path = find_path(shell, exec->cmd);
	if (path == NULL)
		return ((free_child_shell(&shell)));
	if (execve(path, exec->args, shell->env) == -1)
	{
		if (path)
			free(path);
		perror("Error excecuting execve\n");
	}
}

int	any_cmd_waiter(t_minishell *shell)
{
	int	status;

	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			shell->status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			shell->status = WTERMSIG(status) + 128;
	}
	return (shell->status);
}

int	one_cmd_waiter(t_minishell *shell)
{
	int	status;

	while (waitpid(shell->pid, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			shell->status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			shell->status = WTERMSIG(status) + 128;
	}
	return (shell->status);
}
