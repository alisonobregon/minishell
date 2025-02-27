/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 19:56:47 by gongarci          #+#    #+#             */
/*   Updated: 2025/02/26 21:26:16 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


char	*find_path(t_minishell *shell, char *cmd)
{
	char	**paths;
	char	*goodpath;
	int		i;

	i = 0;
	if ((cmd[0] == '/' && access(cmd, 0) == 0))
		return (cmd);
	while(shell->env[i] && ft_strncmp(shell->env[i], "PATH=", 5))
		i++;
	paths = ft_split(shell->env[i] + 5, ':');
	cmd = ft_strjoin("/", cmd);
	i = -1;
	while (paths[++i])
	{
		goodpath = ft_gnlstrjoin(paths[i], cmd, ft_strlen(cmd));
		if (access(goodpath, 0) == 0)
			return (goodpath);
		free(goodpath);
	}
	ft_putstr_fd(cmd, 2);
	perror("Command not found");
	return (NULL);
	
}
