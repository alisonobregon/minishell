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

int	check_binary(t_minishell *shell, t_exec *exec, char *cmd)
{
	if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == 0)
	{
		if (ft_strchr(cmd, '/'))
			return (execve(cmd, exec->args, shell->env), 1);
		return (0);
	}
	else if (access(cmd, F_OK) == 0 && access(cmd, X_OK) != 0)
		return (perror("Permission denied"), -1);
	return (0);
}

char	*find_path(t_minishell *shell, char *cmd)
{
	char	**paths;
	char	*goodpath;
	char	*bar_cmd;
	int		i;

	i = 0;
	if (ft_strlen(cmd) > 1)
	{
		while (shell->env[i] && ft_strncmp(shell->env[i], "PATH=", 5))
			i++;
		paths = ft_split(shell->env[i] + 5, ':');
		bar_cmd = ft_strjoin("/", cmd);
		i = -1;
		while (paths[++i])
		{
			goodpath = ft_strjoin(paths[i], bar_cmd);
			if (access(goodpath, 0) == 0)
				return (free(bar_cmd), free_array(paths), goodpath);
			free(goodpath);
		}
	}
	if (ft_strlen(cmd) > 1)
		(free_array(paths), free(bar_cmd));
	return ((ft_putstr_fd("-Minishell: ", 2), NULL));
}
