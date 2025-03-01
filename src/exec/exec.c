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
	(void)pre_pipe;
	//if (exec->todo_next == 2 && exec->next->todo_next == 0 && shell->exec->i == 0)
	if (shell->exec->i == 0 && exec->todo_next == 2)
	{
		//if fdin !=0 then dup2(fdin, STDIN_FILENO)
		printf("pipe 1 \n");
		//if fdout !=1 then dup2(fdout, STDOUT_FILENO)
		close(pipe_fd[0]);//close unused read end
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		//if we have fd out different than stdout we have to close it
		exec_cmd(shell, exec);
	}
				//else if (exec->todo_next == 2 && exec->next->todo_next == 2 && shell->exec->i >= 0)
	else if (shell->exec->i <= (len_pipes(shell->exec) - 1))
	{
		printf("pipe 2 \n");
		close(pipe_fd[0]);
		dup2(pre_pipe[0], STDIN_FILENO);
		close(pre_pipe[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		close(pre_pipe[1]);
		exec_cmd(shell, exec);
	}
	else if (exec->todo_next == 0 && shell->exec->i > 0)
	{
		printf("pipe 3 \n");
		close(pipe_fd[1]); //close unused write end
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		exec_cmd(shell, exec);
	}
	exit(127);
}

static int pipex(t_minishell *shell)
{
	t_exec	*exec;
	int	*pipe_fd;
	int	*pre_pipe;

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
			handler_fd(shell, exec, pipe_fd, pre_pipe);
		if (shell->exec->i >= 1)
			close(pre_pipe[0]);
		ft_int_memcpy(pre_pipe, pipe_fd, 2);
		close(pipe_fd[1]);
		exec = exec->next;
		shell->exec->i++;
	}
	/* close(pipe_fd[1]);
	close(pipe_fd[0]); */
	while (wait(NULL) > 0)
		;
	return (0);
}

void	exec(t_minishell *shell)
{
	t_exec	*exec;
	
	char *path;
	if (!shell->exec || ft_strlen(shell->prompt->str) <= 1)
		return ;
	exec = shell->exec;
	printf("father\n");
	if (exec && exec->todo_next == 0) // 1 cmd case
	{
		shell->pid = fork();
		if (shell->pid == -1)
		{
			perror("fork");
			return ;
		}
		else if (shell->pid == 0)
		{
			path = find_path(shell, exec->cmd);
			if (execve(path, exec->args, shell->env) == -1)
			{
				perror("execve");
				exit(1);
			}
		}
	}
	else if (exec && exec->todo_next == 2) // 2 cmd or more cmds case
	{
		pipex(shell);
	}
}