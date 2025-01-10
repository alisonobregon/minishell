/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:13:07 by marvin            #+#    #+#             */
/*   Updated: 2025/01/10 18:13:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*char	*find_path(t_minishell *shell)
{
	//char	**paths;
	//char	*goodpath;
	//char	*command;
	int		i;

	i = 0;
	command = ft_strdup(cmd);
	if ((cmd[0] == '/' && access(cmd, 0) == 0))
		return (cmd); 
	while (shell->env[i] && ft_strncmp(shell->env[i], "PATH=", 5))
		i++;
	//shell->path = ft_split(shell->env[i] + 5, ':');
	shell->path = shell->env[i];
	printf("paths: %s\n", shell->path);
	return (NULL);
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
}*/

/* void	check_prompt(t_minishell *shell)
{
	int i;

	i = 0;
	shell->prompt->prompt = ft_split(shell->prompt->line, ' ');
	while(shell->prompt->prompt[i] != NULL)
	{
		if (ft_strmcmp(shell->prompt->prompt[i]), "<<", 2 == 0)
		{
			//heredoc++;
		}
		else if (ft_strmcmp)
	}
} */