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

void	fd_checker(t_exec *exec)
{
	if (exec->infile != NULL)
	{
		printf("aqu no debo entrar\n");
			if (exec->infile[0])
			{
				if (access(exec->infile[0], F_OK) == -1)
				{
					perror("File not found");
					exit(1);
				}
				exec->fd_in = open(exec->infile[0], O_RDONLY);
				printf("opening fd %d \n", exec->fd_in);
			}
	}
	printf("entra aquiiii zzzzz\n");
	printf("outfile dentro de exec: %s\n", exec->outfile->file);
	if(exec->outfile->file == NULL)
	{
		printf("outfile es null\n");
	}
	else
	{
		printf("outfile no es null\n");
	}
	if (exec->outfile != NULL)
	{
		printf("getting outfile\n");
		if (exec->outfile->action == 0)
			exec->outfile->fd_out = open(exec->outfile->file, O_WRONLY | O_CREAT | O_TRUNC, 0664);
		else if (exec->outfile->action == 1)
			exec->outfile->fd_out = open(exec->outfile->file, O_WRONLY | O_CREAT | O_APPEND, 0664);
	}
}

int	len_pipes(t_exec *exec)
{
	int		len;

	len = 0;
	while (exec)
	{
		if (exec->todo_next == 2)
			len++;
		exec = exec->next;
	}
	return (len);
}
