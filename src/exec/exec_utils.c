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

void	fd_checker(t_exec **exec)
{
	t_exec *tmp;

	tmp = (*exec);
	printf("inside fd checker pointer %p\n", *exec);
	if ((*exec)->infile)
	{
		printf("aqui debo entrar\n");
		if ((*exec)->infile[0])
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
		}
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
		dup2(exec->fd_in, STDIN_FILENO);
		close(exec->fd_in);
	}
	if (exec->fd_out != 1)
	{
		dup2(exec->fd_out, STDOUT_FILENO);
		close(exec->fd_out);
	}
}
