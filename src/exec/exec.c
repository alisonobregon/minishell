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

void	exec_cmd(t_minishell *shell, t_exec *exec)
{
	char *path;

	path = find_path(shell, exec->cmd);
	execve(path, exec->args, shell->env);
	perror("Error excecuting execve\n");
	exit(1);
}

void	handler_fd(t_minishell *shell, t_exec *exec, int *pipe_fd, int *pre_pipe)
{
	//if (exec->todo_next == 2 && exec->next->todo_next == 0 && shell->exec->i == 0)
	if (shell->exec->i == 0 && exec->todo_next == 2)
	{
		printf("pipe 1 \n");
		printf("fd_in %d\n", exec->fd_in);
		if (exec->fd_in != 0)
		{
			dup2(exec->fd_in, STDIN_FILENO);
			close(exec->fd_in);
		}
		close(pipe_fd[READ]);
		dup2(pipe_fd[WRITE], STDOUT_FILENO);
		close(pipe_fd[WRITE]);
		exec_cmd(shell, exec);
	}
	//else if (exec->todo_next == 2 && exec->next->todo_next == 2 && shell->exec->i >= 0)
	else if (shell->exec->i <= (len_pipes(shell->exec) - 1))
	{
		printf("pipe 2 \n");
		close(pipe_fd[READ]);
		dup2(pre_pipe[READ], STDIN_FILENO);
		close(pre_pipe[READ]);
		dup2(pipe_fd[WRITE], STDOUT_FILENO);
		close(pipe_fd[WRITE]);
		close(pre_pipe[WRITE]);
		exec_cmd(shell, exec);
	}
	else if (exec->todo_next == 0 && shell->exec->i > 0)
	{
		printf("pipe 3 \n");
		close(pipe_fd[WRITE]); //close unused write end
		if (exec->fd_in != 0 && exec->infile) // ls | cat < infile case
		{
			printf("fd_in %d\n", exec->fd_in);
			close(pipe_fd[READ]);
			close(exec->fd_in);
			exec->fd_in = open(exec->infile[0], O_RDONLY);
			if (exec->fd_in == -1)
			{
				perror("Error opening file");
				exit(1);
			}
			dup2(exec->fd_in, STDIN_FILENO);
			close(exec->fd_in);
		}
		else
		{
			dup2(pipe_fd[READ], STDIN_FILENO);
			close(pipe_fd[READ]);
		}
		if (exec->outfile && exec->fd_out > 1)
		{
			dup2(exec->fd_out, STDOUT_FILENO);
			close(exec->fd_out);
		}
		exec_cmd(shell, exec);
	}
	exit(127);
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
	while(exec)
	{
		if (exec->todo_next == 2)
		{
			printf("pipe\n");
			if (pipe(pipe_fd) == -1)
			{
				perror("Error creating pipe");
				return (1);
			}
		}
		shell->pid = fork();
		if (shell->pid == -1)
		{
			perror("fork");
			return (1);
		}
		if (shell->pid == 0)
		{
			if (exec->outfile || exec->infile)
				fd_checker(&exec);
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
	free(pipe_fd);
	free(pre_pipe);
	return (0);
}

void	exec(t_minishell *shell)
{
	t_exec	*exec;
	
	char *path;
	if (!shell->exec || ft_strlen(shell->prompt->str) <= 1)
		return ;
	exec = shell->exec;
	print_command_list(exec);
	if (exec && exec->todo_next == 0) // 1 cmd case
	{
		shell->pid = fork();
		if (shell->pid == -1)
		{
			printf("fork error \n");
			return ;
		}
		else if (shell->pid == 0)
		{
			path = find_path(shell, exec->cmd);
			if (exec->outfile || exec->infile)
			{
				printf("in fd checker\n");
				printf(" exec pointer %p\n", exec);
				fd_checker(&exec);
			}
			printf("fd_in %d\n", exec->fd_in);
			if (exec->fd_in != 0)
			{
				dup2(exec->fd_in, STDIN_FILENO);
				close(exec->fd_in);
			}
			if (exec->outfile && exec->fd_out != 1)
			{
				//if exec->fd_out !=1
				printf("fd_out  in child 1 cmd %d\n", exec->fd_out);
				dup2(exec->fd_out, STDOUT_FILENO);
				close(exec->fd_out);
			}
			if (execve(path, exec->args, shell->env) == -1)
			{
				perror("execve");
				exit(1);
			}
		}
		while (wait(NULL) > 0)
		;
	}
	else if (exec && exec->todo_next == 2)
		pipex(shell);
}
