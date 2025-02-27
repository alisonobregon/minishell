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

void	exec_cmd(t_minishell *shell, t_exec *exec, int read, int write)
{
	char *path;

	if (read != 0)
	{
		dup2(read, STDIN_FILENO);
		close(read);
	}
	if (write != 1)
	{
		dup2(write, STDOUT_FILENO);
		close(write);
	}
	path = find_path(shell, exec->cmd);
	if (execve(path, exec->args, shell->env) == -1)
	{
		perror("Error excecuting execve\n");
		exit(1);
	}
}
void	handler_fd(t_minishell *shell, t_exec *exec, int *pipe_fd, int *pre_pipe)
{
	(void)pre_pipe;
	if (exec->todo_next == 2)
	{
		printf("pipe ls  pipe fd1 %d\n", pipe_fd[1]);
		close(pipe_fd[0]);
		exec_cmd(shell, exec, 0, pipe_fd[1]);
		//close(pipe_fd[1]);
	}
	else if (exec->todo_next == 0)
	{
		printf("pipe grep  pipe fd 0 %d\n", pipe_fd[0]);
		close(pipe_fd[1]);
		exec_cmd(shell, exec, pipe_fd[0], 1);
	}
	/* else if ()
	{
		close(pre_pipe[1]);
		exec_cmd(shell, pre_pipe[0], 1);
	} */

}

static int pipex(t_minishell *shell)
{
	t_exec	*exec;
	int	*pipe_fd;
	int	*pre_pipe;

	exec = shell->exec;
	pipe_fd = ft_calloc(2, sizeof(int));
	pre_pipe = ft_calloc(2, sizeof(int));
	if (!pipe_fd || !pre_pipe)
		return (1);
	while(shell->exec != NULL)
	{
		if (exec->todo_next == 2)
		{
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
			handler_fd(shell, shell->exec, pipe_fd, pre_pipe);
		shell->exec = shell->exec->next;
		/* if (exec->todo_next == 2) handle multiple pipes
		{
			close(pipe_fd[1]);
			pre_pipe[0] = pipe_fd[0];
		} */
		
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	while (wait(NULL) > 0)
		;
	return (0);
}

void	exec(t_minishell *shell)
{
	t_exec	*exec;
	
	char *path;
	//char **all_cmd;
	if (!shell->exec || ft_strlen(shell->prompt->str) <= 1)
		return ;
	exec = shell->exec;
	printf("father\n");
	//print_command_list(exec);
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