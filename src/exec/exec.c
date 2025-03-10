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
	close(pipe_fd[READ]);
	close(pre_pipe[WRITE]);
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
	else if (exec->infile == NULL && exec->outfile)
	{
		dup2(pre_pipe[READ], STDIN_FILENO);
		close(pre_pipe[READ]);
		close(pipe_fd[WRITE]);
	}
	else
		multi_dup(pre_pipe[READ], pipe_fd[WRITE]);
}

void	handler_fd(t_minishell *shell, t_exec *exec, int *pipe_fd, int *pre_pipe)
{
	if (shell->exec->i == 0 && exec->todo_next == 2)
	{
		close(pipe_fd[READ]);
		if (exec->fd_out > 1)
			close(pipe_fd[WRITE]);
		else
		{
			multi_dup(exec->fd_in, pipe_fd[WRITE]);
			close(pipe_fd[WRITE]);
		}
	}
	else if (shell->exec->i <= (len_pipes(shell->exec) - 1))
		middle_case(exec, pipe_fd, pre_pipe);
	else if (exec->todo_next == 0 && shell->exec->i > 0)
	{
		close(pipe_fd[WRITE]);
		if (exec->fd_in != 0 && exec->infile)
			close(pipe_fd[READ]);
		else
		{
			dup2(pipe_fd[READ], STDIN_FILENO);
			close(pipe_fd[READ]);
		}
	}
	exec_cmd(shell, exec);
}

static int pipex(t_minishell *shell)
{
	t_exec	*exec;
	int		*pipe_fd;
	int		*pre_pipe;

	exec = shell->exec;
	shell->exec->i = 0;
	pipe_fd = ft_calloc(2, sizeof(int));
	pre_pipe = ft_calloc(2, sizeof(int));
	if (!pipe_fd || !pre_pipe)
		return (1);
	while (exec)
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
			perror("fork");
			(free(pipe_fd), free(pre_pipe));
			return (1);
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
		if (shell->exec->i >= 1)
			close(pre_pipe[READ]);
		ft_int_memcpy(pre_pipe, pipe_fd, 2);
		close(pipe_fd[WRITE]);
		exec = exec->next;
		shell->exec->i++;
	}
	while (wait(NULL) > 0)
		;
	//close some fds probably piepes;
	free(pipe_fd);
	free(pre_pipe);
	return (1);
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
			fd_checker(&shell->exec);
		exec_cmd(shell, shell->exec);
	}
	while (wait(NULL) > 0)
		;
}

void	exec(t_minishell *shell)
{
	t_exec	*exec;

	if (!shell->exec || ft_strlen(shell->prompt->str) <= 1)
		return ;
	exec = shell->exec;
	print_command_list(exec);
	here_doc(exec);
	if (exec && exec->todo_next == 0)
	{
		one_cmd(shell);
	}
	else if (exec && exec->todo_next == 2)
	{
		pipex(shell);
	}
}
