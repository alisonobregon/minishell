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
		//if fdin !=0 then dup2(fdin, STDIN_FILENO)
	/* 	if (exec->fd_in != 0)
		{
			dup2(exec->fd_in, STDIN_FILENO);
			close(exec->fd_in);
		} */
		printf("pipe 1 \n");
		//if fdout !=1 then dup2(fdout, STDOUT_FILENO)
		if (exec->outfile)
		{
			if (exec->fd_out != 1)
				close(exec->fd_out);
		}
		close(pipe_fd[READ]);//close unused read end
		dup2(pipe_fd[WRITE], STDOUT_FILENO);
		close(pipe_fd[WRITE]);
		//if we have fd out different than stdout we have to close it
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
		exec->fd_out = 2;
		exec->next->fd_out = 3;
		close(pipe_fd[WRITE]); //close unused write end
		dup2(pipe_fd[READ], STDIN_FILENO);
		close(pipe_fd[READ]);
		if (exec->outfile)
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
			fd_checker(exec);
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
	if (exec && exec->todo_next == 0) // 1 cmd case
	{
		printf("father\n");
		shell->pid = fork();
		printf("pid %d\n", shell->pid);
		if (shell->pid == -1)
		{
			printf("fork error \n");
			return ;
		}
		else if (shell->pid == 0)
		{
			//printf("son\n");
			//printf("son  whyyyyyy checking fd %d\n", exec->outfile->fd_out);
			path = find_path(shell, exec->cmd);
			fd_checker(exec);
			//printf("checking fd %d\n", exec->outfile->fd_out);
			if (exec->outfile->file && exec->outfile->fd_out > 1)
			{
				printf("fd_out  in child 1 cmd %d\n", exec->fd_out);
				dup2(exec->outfile->fd_out, STDOUT_FILENO);
				close(exec->outfile->fd_out);
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
	else if (exec && exec->todo_next == 2) // 2 cmd or more cmds case
		pipex(shell);
}


/* char **outfie = {["fd"], ["fd2"], ["fd3"]};
int	**action = {[0], [1], [1]};

char file - fd    0   fd_checker
char file - fd2   1   fd_checker
 */