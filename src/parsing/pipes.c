/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliobreg <aliobreg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 20:53:31 by aliobreg          #+#    #+#             */
/*   Updated: 2025/04/08 20:53:31 by aliobreg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	signals_pipes(char **buf, char *pipe)
{
	char	*temp;

	while (1 && !g_sigint)
	{
		pipe = readline("pipe>");
		if (g_sigint)
		{
			ft_printf("\n");
			break ;
		}
		if (!pipe)
		{
			ft_printf("bash: syntax error\n");
			exit(2);
		}
		if (pipe && *pipe)
		{
			temp = ft_strjoin(*buf, pipe);
			free(pipe);
			free(*buf);
			*buf = temp;
			break ;
		}
		free(pipe);
	}
}

void	ft_pipes(char **buf)
{
	int		i;
	char	*pipe;

	i = -1;
	pipe = NULL;
	while ((*buf)[++i])
	{
		if (get_arg_type(&((*buf)[i])) == 2)
		{
			if (i == 0)
				return ;
			else
				i++;
			while ((*buf)[i] >= 1 && (*buf)[i] <= 32)
				i++;
			if ((*buf)[i] == '\0')
			{
				signals_pipes(buf, pipe);
			}
		}
	}
}
