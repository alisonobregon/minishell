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

/* int pipex(t_minishell *shell)
{
	int	*pipe_fd;
	int	*pre_pipe;
	int	i;

	i = 0;

	pipe_fd = ft_calloc(2, sizeof(int));
	pre_pipe = ft_calloc(2, sizeof(int));
	if (!pipe_fd || !pre_pipe)
		return (1);
	while(shell->exec != NULL)
	{
		shell->pid = fork();
		if (shell->pid == -1)
		{
			perror("fork");
			return (1);
		}
		
	}
} */

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
			//all_cmd = ft_split(exec->cmd, ' ');
			path = find_path(shell);
			if (execve(path, exec->args, shell->env) == -1)
			{
				perror("execve");
				exit(1);
			}
		}
	}
	else if (exec && exec->todo_next) // 2 cmd case
	{
		//pipex(shell);
	}
}