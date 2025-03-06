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

void	infile_checker(t_exec **exec)
{
	int i;

	i = 0;
	if ((*exec)->infile)
	{
		printf("many infile  %d\n", ft_len((*exec)->infile));
		while (i < ft_len((*exec)->infile))
		{
			printf("infile %s\n", (*exec)->infile[i]);
			if (access((*exec)->infile[i], F_OK))
			{
				perror("File not found");
				exit(1);
			}
			if (access((*exec)->infile[i], R_OK))
			{
				perror("Permission denied");
				exit(1);
			}
			if (!(*exec)->infile[i + 1])
			{
				printf("taking infile %s\n", (*exec)->infile[i]);
				(*exec)->fd_in = open((*exec)->infile[i], O_RDONLY);
				close((*exec)->fd_in);
			}
			i++;
		}
	}
}

void	fd_checker(t_exec **exec)
{
	t_exec *tmp;

	tmp = (*exec);
	printf("inside fd checker pointer %p\n", *exec);
	if ((*exec)->infile)
	{
		printf("aqui debo entrar\n");
		infile_checker(exec);
		/* if ((*exec)->infile[0])
		{
			if (access((*exec)->infile[0], F_OK) == -1)
			{
				perror("File not found");
				//free child
				exit(1);
			}
			(*exec)->fd_in = open((*exec)->infile[0], O_RDONLY);
			printf("opening file %s\n", (*exec)->infile[0]);
			printf("opening fd %d \n", (*exec)->fd_in);
		} */
	}
	if (!(*exec)->outfile)
		return ;
	while ((*exec)->outfile->next != NULL)
	{
		//if (access((*exec)->outfile->file, F_OK) == -1)
		if ((*exec)->outfile->action == 0)
			close(open((*exec)->outfile->file, O_WRONLY | O_CREAT | O_TRUNC, 0664));
		else
			close(open((*exec)->outfile->file, O_WRONLY | O_CREAT | O_APPEND, 0664));
		(*exec)->outfile = (*exec)->outfile->next;
	}
	if ((*exec)->outfile->next == NULL)
	{
		if ((*exec)->outfile->action == 0)
			tmp->fd_out = open((*exec)->outfile->file, O_WRONLY | O_CREAT | O_TRUNC, 0664);
		else if ((*exec)->outfile->action == 1)
			tmp->fd_out = open((*exec)->outfile->file, O_WRONLY | O_CREAT | O_APPEND, 0664);
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

void	dup_checker(t_exec *exec)
{
	if (exec->fd_in != 0)
	{
		//open(exec->infile[ft_len(exec->infile) - 1], O_RDONLY);
		dup2(exec->fd_in, STDIN_FILENO);
		close(exec->fd_in);
	}
	if (exec->fd_out != 1)
	{
		dup2(exec->fd_out, STDOUT_FILENO);
		close(exec->fd_out);
	}
}
