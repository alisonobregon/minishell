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
/*che boluda acuerdate hay que hablar del gnl :)*/
char	*doc_fd(char *limiter)
{
	char	*line;
	int		temp_fd;
	char *tmp;

	tmp = NULL;
	other_signals();
	if (limiter[0] == '\'')
	{
		tmp = ft_strdup(limiter);
		limiter = ft_strtrim(tmp, "'");
		free(tmp);
	}
	if (limiter[0] == '\"')
	{
		tmp = ft_strdup(limiter);
		limiter = ft_strtrim(tmp, "\"");
		free(tmp);
	}
	temp_fd = open(limiter, O_CREAT | O_WRONLY, 0644);
	if (temp_fd < 0)
		return (ft_printf("Error creating temp file\n"), NULL);
	// ft_printf("> ");
	// line = get_next_line(0);
	while (/*line &&*/ !g_sigint)
	{
		ft_printf("> ");
		line = get_next_line(0);
		if (g_sigint || !line)
			break ;
		// {
		// 	free(line);
		// 	close(temp_fd);
		// 	printf("\n");
		// 	return (NULL);
		// }
		if ((ft_strlen(line) - 1) == ft_strlen(limiter))
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
				break ;
		ft_putstr_fd(line, temp_fd);
		free(line);
	}
	free(line);
	close(temp_fd);
	wait_signal();
	return (limiter);
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
		doc_infile	= doc_fd(limiter);
	if (doc_infile)
		(*exec)->infile = add_str_to_array((*exec)->infile, doc_infile);
	return ;
}
