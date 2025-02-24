/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 19:56:47 by gongarci          #+#    #+#             */
/*   Updated: 2025/02/24 19:57:21 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*find_path(char *cmd, t_pipex *data, t_values *vals)
{
	char	**paths;
	char	*goodpath;
	char	*command;
	int		i;

	i = 0;
	command = ft_strdup(cmd);
	if ((cmd[0] == '/' && access(cmd, 0) == 0))
		return (cmd);
	while (vals->env[i] && ft_strncmp(vals->env[i], "PATH=", 5))
		i++;
	paths = ft_split(vals->env[i] + 5, ':');
	cmd = ft_strjoin("/", cmd);
	i = -1;
	while (paths[++i])
	{
		goodpath = ft_gnlstrjoin(paths[i], cmd, ft_strlen(cmd));
		if (access(goodpath, 0) == 0)
			return (goodpath);
		free(goodpath);
	}
	ft_putstr_fd(command, 2);
	return (ft_error(": command not found\n", 127, data, vals), NULL);
}
