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

int	pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("minishell: pwd: error retrieving current directory");
		return (0);
	}
	ft_printf("%s\n", cwd);
	free(cwd);
	return (1);
}

static int	new_path(t_minishell *shell, char **arr)
{
	char	*new_path;

	new_path = ft_strdup(arr[1]);
	if (new_path == NULL)
	{
		ft_printf("minishell: cd: memory allocation error\n");
		return (-1);
	}
	new_path = ft_gnlstrjoin(new_path, "/", 1);
	if (chdir(new_path) == -1)
	{
		ft_printf("minishell: cd: %s: No such file or directory\n", new_path);
		free(new_path);
		return (1);
	}
	shell->cwd = get_prompt(shell);
	free(new_path);
	return (1);
}

int	cd(t_minishell *shell, char **arr)
{
	char	*home;

	home = get_env("$HOME", shell->env, shell->status);
	if (ft_len(arr) > 2)
	{
		ft_printf("minishell: cd: too many arguments\n");
		return (1);
	}
	if (arr[1] == NULL || !ft_strncmp(arr[1], "~", 2))
	{
		if (home == NULL)
		{
			ft_printf("minishell: cd: HOME not set\n");
			return (free(home), 1);
		}
		chdir(home);
		shell->cwd = get_prompt(shell);
		return (free(home), 1);
	}
	free(home);
	return (new_path(shell, arr));
}
