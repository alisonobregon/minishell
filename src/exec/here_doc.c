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
	int		i;
	char	*tmp;

	i = 0;
	if (!heredoc)
		return ;
	while (heredoc[i])
	{
		tmp = ft_strjoin(heredoc[i], ".tmp");
		unlink(tmp);
		free(tmp);
		i++;
	}
}

char	*doc_fd(char *limit)
{
	char	*line;
	int		temp_fd;
	char	*limiter;

	other_signals();
	limiter = ft_str2join(limit, ".tmp", 0, 0);
	limiter = quit_quotes(limiter);
	temp_fd = open(limiter, O_CREAT | O_WRONLY, 0644);
	if (temp_fd < 0)
		return (ft_printf("Error creating temp file\n"), NULL);
	while (!g_sigint)
	{
		ft_printf("> ");
		line = get_next_line(0);
		if (g_sigint || !line)
			break ;
		if ((ft_strlen(line) - 1) == ft_strlen(limit))
			if (ft_strncmp(line, limit, ft_strlen(limit)) == 0)
				break ;
		ft_putstr_fd(line, temp_fd);
		free(line);
	}
	wait_signal();
	return (free(line), close(temp_fd), limiter);
}

void	here_doc(t_exec **exec, char *limiter)
{
	char	*doc_infile;

	if (!exec)
		return ;
	doc_infile = NULL;
	if (!(*exec)->heredoc)
		return ;
	if ((*exec)->heredoc)
		doc_infile = doc_fd(limiter);
	if (doc_infile)
		(*exec)->infile = add_str_to_array((*exec)->infile, doc_infile);
	free(doc_infile);
	return ;
}
