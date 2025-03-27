/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 19:58:26 by gongarci          #+#    #+#             */
/*   Updated: 2025/02/26 21:59:29 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	middle_case(t_exec *exec, int *pipe_fd, int *pre_pipe)
{
	if (exec->fd_in != 0 && !exec->outfile)
	{
		close(pre_pipe[READ]);
		dup2(pipe_fd[WRITE], STDOUT_FILENO);
		close(pipe_fd[WRITE]);
	}
	else if (exec->fd_in != 0 && exec->outfile)
	{
		close(pipe_fd[WRITE]);
		close(pre_pipe[READ]);
	}
	else if (!exec->infile && exec->outfile)
	{
		close(pipe_fd[WRITE]);
		dup2(pre_pipe[READ], STDIN_FILENO);
		close(pre_pipe[READ]);
	}
	else
		multi_dup(pre_pipe[READ], pipe_fd[WRITE]);
	close(pipe_fd[READ]);
	close(pre_pipe[WRITE]);
}

void	handler_fd(t_minishell *s, t_exec *exec, int *pipe_fd, int *pre_pipe)
{
	if (s->exec->i == 0 && exec->todo_next == 2)
	{
		close(pipe_fd[READ]);
		if (exec->fd_out > 1)
			close(pipe_fd[WRITE]);
		else
			multi_dup(exec->fd_in, pipe_fd[WRITE]);
	}
	else if (s->exec->i <= (len_pipes(s->exec) - 1))
		middle_case(exec, pipe_fd, pre_pipe);
	else
	{
		close(pipe_fd[WRITE]);
		if (exec->fd_in != 0 && exec->infile)
			close(pipe_fd[READ]);
		else
		{
			dup2(pipe_fd[READ], STDIN_FILENO);
			close(pipe_fd[READ]);
			close(pre_pipe[WRITE]);
		}
	}
	unlinker(exec->heredoc);
	if (!exec_builtin(s, exec->cmd, exec->args))
		exec_cmd(s, exec);
	exit(1);
}

int	child_maker(t_minishell *shell, t_exec *exec, int *pipe_fd, int *pre_pipe)
{
	if (exec->todo_next == 2)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("Error creating pipe");
			return ((free(pipe_fd), free(pre_pipe), 0));
		}
	}
	shell->pid = fork();
	if (shell->pid == -1)
	{
		perror("error in fork");
		return ((free(pipe_fd), free(pre_pipe), 1));
	}
	if (shell->pid == 0)
	{
		if (exec->outfile || exec->infile)
		{
			if (!fd_checker(&exec))
				return ((free(pipe_fd), free(pre_pipe)), 0);
		}
		handler_fd(shell, exec, pipe_fd, pre_pipe);
	}
	return (1);
}

static int	pipex(t_minishell *shell)
{
	t_exec	*exec;
	int		*pipe_fd;
	int		*pre_pipe;

	exec = shell->exec;
	shell->exec->i = 0;
	pipe_fd = ft_calloc(2, sizeof(int));
	pre_pipe = ft_calloc(2, sizeof(int));
	if (!pipe_fd || !pre_pipe)
		return (0);
	while (exec)
	{
		if (!child_maker(shell, exec, pipe_fd, pre_pipe))
			return (0);
		if (shell->exec->i >= 1)
			close(pre_pipe[READ]);
		ft_int_memcpy(pre_pipe, pipe_fd, 2);
		close(pipe_fd[WRITE]);
		exec = exec->next;
		shell->exec->i++;
	}
	while (wait(NULL) > 0)
		;
	(close(pipe_fd[READ]), close(pre_pipe[WRITE]));
	return (free(pre_pipe), free(pipe_fd), 1);
}

void	exec(t_minishell *shell)
{
	t_exec	*exec;

	if (!shell->exec)
		return ;
	exec = shell->exec;
	if (exec && exec->todo_next == 0)
		one_cmd(shell);
	else if (exec && exec->todo_next == 2)
	{
		if (!pipex(shell))
		{
			ft_putstr_fd("Error in pipex\n", 2);
			exit(1);
		}
	}
}
