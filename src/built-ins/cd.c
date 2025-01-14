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

//setenv
//chdir
//getcwd
//getenv

static int	new_path(t_minishell *shell, char **str)
{
	char	*new_path;

	new_path = ft_strdup(*str + 3);
	ft_printf("new_path: %s\n", new_path);
	new_path = ft_gnlstrjoin(new_path, "/", 1);
	if (chdir(new_path) == -1)
	{
		ft_printf("-bash 1: cd: %s: No such file or directory\n", new_path);
		free(new_path);
		return (0);
	}
	else
	{
		ft_printf("new_path: %s\n", new_path);
		chdir(new_path);
		shell->cwd = new_path;
		free(new_path);
	}
	return (1);
}

int cd(t_minishell *shell, char **str)
{
	char	*home;

	home = getenv("HOME");
	ft_printf("str: %s\n", *str);
	if (!ft_strncmp(*str, "cd ~", 4) || !ft_strncmp(*str, "cd", ft_strlen(*str)))
	{
		ft_printf("home case\n");
		if (home == NULL)
			return (1);
		chdir(home);
		shell->cwd = home;
			return (1);
	}
	else if (ft_strlen(*str) > 3)
	{
		new_path(shell, str);
		return (1);
	}
	return (0);
}
