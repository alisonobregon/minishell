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

int	doc_fd(t_exec *exec, char *limiter)
{
	char	*line;
	int		temp_fd;
	(void)exec;
	temp_fd = open("temp_file", O_CREAT | O_WRONLY, 0644);
	if (temp_fd < 0)
		return (ft_printf("Error creating temp file\n"), -1);
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
	return (temp_fd);
}

void	here_doc(t_exec *exec)
{
	int	i;

	i = 0;
	if (!exec->heredoc)
		return ;
	while (exec->heredoc[i] != NULL)
	{
		if (exec->heredoc)
			exec->fd_in = doc_fd(exec, exec->heredoc[i]);
		//exec = exec->next;
		i++;
	}
	return ;
}

//  write  and make the temporal file, and add it to the list of infile order
// in order to check if first or last one to be taken
// sorts infile !!
// 1. check if here_doc is present
// 2. if present, create a temporal file
// 3. write in the temporal file until the limiter is found
// 4. close the file
// 5. add the file to the infile list
// 6. go to the next exec
// 7. repeat until no more here_doc

// one possible solution 
// to find the index of infile is to create a list of infile