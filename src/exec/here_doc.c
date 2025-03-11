/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:28:35 by marvin            #+#    #+#             */
/*   Updated: 2025/03/10 17:28:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	unlinker(char **heredoc)
{
	int	i;

	i = 0;
	if (!heredoc)
		return ;
	while (heredoc[i])
		unlink(heredoc[i++]);
}

char	*doc_fd(char *limiter)
{
	char	*line;
	int		temp_fd;

	printf("limiter %s\n", limiter);
	temp_fd = open(limiter, O_CREAT | O_WRONLY, 0644);
	if (temp_fd < 0)
		return (ft_printf("Error creating temp file\n"), NULL);
	ft_printf("> ");
	line = get_next_line(0);
	while (line)
	{
		ft_printf("> ");
		if ((ft_strlen(line) - 1) == ft_strlen(limiter))
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
				break ;
		ft_putstr_fd(line, temp_fd);
		free(line);
		line = get_next_line(0);
	}
	free(line);
	close(temp_fd);
	printf("temp_file: %s\n", limiter);
	return (limiter);
}

void	here_doc(t_exec **exec, char *limiter)
	
{
	char	*doc_infile;

	printf("HERE DOC\n");
	printf(" in hd limiter: %s\n", limiter);
	doc_infile = NULL;
	if (!exec)
		return ;
	if (!(*exec)->heredoc)
	return ;
	if ((*exec)->heredoc)
		doc_infile	= doc_fd(limiter);
	if (doc_infile)
		(*exec)->infile = add_str_to_array((*exec)->infile, doc_infile);
	return ;
}
