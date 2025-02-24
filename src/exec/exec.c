/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 19:58:26 by gongarci          #+#    #+#             */
/*   Updated: 2025/02/24 20:04:36 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int pipex(t_minishell *shell)
{
	int	*pipe_fd;
	int	*pre_pipe;
	int	i;

	i = 0;

	pipe_fd = ft_calloc(2, sizeof(int));
	pre_pipe = ft_calloc(2, sizeof(int));
	if (!pipe_fd || !pre_pipe)
		return (1);
	while(shell->exec->cmd != NULL)
	{
		
	}
}
