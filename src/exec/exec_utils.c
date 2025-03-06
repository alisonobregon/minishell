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

void	out_access_checker(t_exec **exec, char	*file)
{
	if ((*exec)->outfile->action == 1)
	{
		if (access(file, W_OK))
		{
			perror("Permission denied");
			//free;
			exit(1);
		}
	}
}

void	infile_checker(t_exec **exec)
{
	int i;

	i = 0;
	if ((*exec)->infile)
	{
		while (i < ft_len((*exec)->infile))
		{
			printf("infile %s\n", (*exec)->infile[i]);
			if (access((*exec)->infile[i], F_OK))
			{
				perror("File not found");
				//free
				exit(1);
			}
			if (access((*exec)->infile[i], R_OK))
			{
				perror("Permission denied");
				exit(1);
			}
			if (!(*exec)->infile[i + 1])
				(*exec)->fd_in = open((*exec)->infile[i], O_RDONLY);
			i++;
		}
	}
}

void	fd_checker(t_exec **exec)
{
	t_exec *tmp;

	tmp = (*exec);
	if ((*exec)->infile)
	{
		infile_checker(exec);
	}
	if (!(*exec)->outfile)
		return ;
	printf("outfile \n");
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

void	dup_checker(t_exec **exec)
{
	if ((*exec)->fd_in != 0)
	{
		dup2((*exec)->fd_in, STDIN_FILENO);
		close((*exec)->fd_in);
	}
	if ((*exec)->fd_out > 1)
	{
		dup2((*exec)->fd_out, STDOUT_FILENO);
		close((*exec)->fd_out);
	}
}
