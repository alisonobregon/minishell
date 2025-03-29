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
	children_signal();
	if (builtin_checker(shell, shell->exec->cmd))
	{
		if (shell->exec->outfile || shell->exec->infile)
		{
			if (!fd_checker(&shell->exec))
			{
				shell->status = 1;
				return ;
			}
		}
		if (exec_builtin(shell, shell->exec->cmd, shell->exec->args) == -1)
		{
			shell->status = 127; //en plan hay que ir poniendo de estos en la ejecucion
			return ;
		}
		multi_dup(shell->exec->stdin, shell->exec->stdout); //aqui puede estarya que no lo asignas
	}
	else
	{
		shell->pid = fork();
		if (shell->pid == -1)
		{
			shell->status = 100;
			return (perror("fork"));
		}
		if (shell->pid == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			if (shell->exec->outfile || shell->exec->infile)
			{
				if (!fd_checker(&shell->exec))
				{
					shell->status = 1;
					return ;
				}
			}
			if (shell->exec->heredoc)
				unlinker(shell->exec->heredoc);
			exec_cmd(shell, shell->exec);
			signal(SIGQUIT, SIG_IGN);
			exit(1);
		}
	}
	while (wait(NULL) > 0)
		;
	//WAIEEXITED

}
