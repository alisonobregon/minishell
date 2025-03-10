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
	int i;

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
				dup2((*exec)->fd_in, STDIN_FILENO);
				if ((*exec)->fd_in != 0)
					close((*exec)->fd_in);
			}
			i++;
		}
	}
	return (1);
}

t_exec	*outfile_checker(t_exec **exec)
{
	t_exec *tmp;

	tmp = (*exec);
	while (tmp->outfile->next != NULL)
	{
		if (!tmp->outfile->action)
		{
			if (!access(tmp->outfile->file, F_OK) && access(tmp->outfile->file, W_OK))
				return (perror("Permission denied"), NULL);
			close(open(tmp->outfile->file, O_WRONLY | O_CREAT | O_TRUNC, 0664));
		}
		else
		{
			if (!access(tmp->outfile->file, F_OK) && access(tmp->outfile->file, W_OK))
				close(open(tmp->outfile->file, O_WRONLY | O_CREAT | O_APPEND, 0664));
			else if (access(tmp->outfile->file, F_OK))
				close(open(tmp->outfile->file, O_WRONLY | O_CREAT | O_APPEND, 0664));
			else
				return (perror("Permission denied"), NULL);
		}
		tmp->outfile = tmp->outfile->next;
	}
	return (tmp);
}

int	fd_checker(t_exec **exec)
{
	t_exec *tmp;

	tmp = (*exec);
	if ((*exec)->infile)
	{
		if (!infile_checker(exec))
			return (0);
	}
	if (!(*exec)->outfile)
		return (2);
/* 	while ((*exec)->outfile->next != NULL)
	{
		//if (access((*exec)->outfile->file, F_OK) == -1)
		if ((*exec)->outfile->action == 0)
			close(open((*exec)->outfile->file, O_WRONLY | O_CREAT | O_TRUNC, 0664));
		else
		{
			//if (access((*exec)->outfile->file, F_OK) == -1)
			close(open((*exec)->outfile->file, O_WRONLY | O_CREAT | O_APPEND, 0664));
		}
		(*exec)->outfile = (*exec)->outfile->next;
	} */
	*exec = outfile_checker(exec);
	if ((*exec)->outfile->next == NULL)
	{
		if ((*exec)->outfile->action == 0)
		{
			tmp->fd_out = open((*exec)->outfile->file, O_WRONLY | O_CREAT | O_TRUNC, 0664);
			if (tmp->fd_out == -1)
				return (perror("Error opening file here"), 0);
			dup2(tmp->fd_out, STDOUT_FILENO);
			if (tmp->fd_out > 1)
				close(tmp->fd_out);
		}
		else if ((*exec)->outfile->action == 1)
		{
			tmp->fd_out = open((*exec)->outfile->file, O_WRONLY | O_CREAT | O_APPEND, 0664);
			if (tmp->fd_out == -1)
				return (perror("Error opening file"), 0);
			dup2(tmp->fd_out, STDOUT_FILENO);
			if (tmp->fd_out > 1)
				close(tmp->fd_out);
		}
	}
	return (1);
}
