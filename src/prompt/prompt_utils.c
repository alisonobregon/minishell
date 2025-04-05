/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 18:20:34 by marvin            #+#    #+#             */
/*   Updated: 2025/03/31 16:10:48 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	add_history_to_file(char *str)
{
	int	fd;

	fd = open(".history", O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (fd == -1)
	{
		perror("open");
		return (1);
	}
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
	close(fd);
	return (0);
}
