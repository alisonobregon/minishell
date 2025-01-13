/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 23:39:35 by marvin            #+#    #+#             */
/*   Updated: 2025/01/12 23:39:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int cd(t_minishell *shell)
{
	char	*path;

	if (ft_strncmp(shell->pwd, "cd", 3) != 0)
		return (0);
	if (shell->pwd == NULL)
	{
		path = getenv("HOME");
		if (path == NULL)
			return (1);
	}
	else
		path = shell->pwd + 3;
	if (chdir(path) == -1) // Si no encuentra la ruta devuelve -1
	{
		ft_printf("-bash: cd: %s: No such file or directory\n", path);
		return (1);
	}
	shell->pwd = getcwd(NULL, 0);
	if (shell->pwd == NULL)
		return (1);
	setenv("PWD", shell->pwd, 1);
	free(shell->pwd);
	return (0);
}
