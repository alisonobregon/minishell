/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 00:33:42 by marvin            #+#    #+#             */
/*   Updated: 2025/03/10 00:33:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	infile_checker(t_exec **exec)
{
	int	i;

	i = 0;
	if ((*exec)->infile)
	{
		while (i < ft_len((*exec)->infile))
		{
			if (access((*exec)->infile[i], F_OK))
				return(perror("File not found"), 0);
			if (access((*exec)->infile[i], R_OK))
				return(perror("Permission denied"), 0);
			if (!(*exec)->infile[i + 1])
			{
				(*exec)->fd_in = open((*exec)->infile[i], O_RDONLY);
				if ((*exec)->fd_in == -1)
					return(perror("Error opening file here"), 0);
				if ((*exec)->fd_in != 0)
				{
					dup2((*exec)->fd_in, STDIN_FILENO);
					close((*exec)->fd_in);
				}
			}
			i++;
		}
	}
	return (1);
}

t_exec	*outfile_checker(t_exec **exec)
{
	t_exec	*t;
	int fd = -1;

	t = (*exec);
	while (t->outfile->next != NULL)
	{
		if (t->outfile->action == 0)
		{
			fd = open((*exec)->outfile->file, O_WRONLY | O_CREAT | O_TRUNC, 0664);
			if (fd == -1)
				return (perror("Error opening file here"), NULL);
			close(fd);
		}
		else
		{
			fd = open((*exec)->outfile->file, O_WRONLY | O_CREAT | O_TRUNC, 0664);
			if (fd == -1)
				return (perror("Error opening file here"), NULL);
			close(fd);
		}
		t->outfile = t->outfile->next;
	}
	return (t);
}

int	take_outfile(t_exec **exec)
{
	if ((*exec)->outfile->next == NULL)
	{
		if ((*exec)->outfile->action == 0)
		{
			(*exec)->fd_out = open((*exec)->outfile->file, O_WRONLY | O_CREAT | O_TRUNC, 0664);
			if ((*exec)->fd_out == -1)
				return (perror("Error opening file here"), 0);
			dup2((*exec)->fd_out, STDOUT_FILENO);
			if ((*exec)->fd_out > 1)
				close((*exec)->fd_out);
		}
		else if ((*exec)->outfile->action == 1)
		{
			(*exec)->fd_out = open((*exec)->outfile->file, O_WRONLY | O_CREAT | O_APPEND, 0664);
			if ((*exec)->fd_out == -1)
				return (perror("Error opening file"), 0);
			if ((*exec)->fd_out > 1)
			{
				dup2((*exec)->fd_out, STDOUT_FILENO);
				close((*exec)->fd_out);
			}
		}
	}
	return (1);
}

int	fd_checker(t_exec **exec)
{
	t_exec	*tmp;

	if ((*exec)->infile)
	{
		if (!infile_checker(exec))
		{
			ft_putstr_fd("infile checker: fail ", 2);
			return (0);
		}
	}
	if (!(*exec)->outfile)
		return (2);
	tmp = outfile_checker(exec);
	if (!tmp)
		return (0);
	if ((*exec) == NULL)
		return (0);
	return (take_outfile(&tmp));
}
