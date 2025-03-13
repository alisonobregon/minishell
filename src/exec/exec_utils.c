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

	path = find_path(shell, exec->cmd);
	execve(path, exec->args, shell->env);
	perror("Error excecuting execve\n");
	exit(1);
}
