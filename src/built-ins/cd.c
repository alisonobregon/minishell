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
	ft_printf("new_path: %s\n", new_path);
	if (new_path == NULL)
	{
		ft_printf("minishell: cd: memory allocation error\n");
		return (0);
	}
	new_path = ft_gnlstrjoin(new_path, "/", 1);
	if (chdir(new_path) == -1)
	{
		ft_printf("-bash 1: cd: %s: No such file or directory\n", new_path);
		free(new_path);
		return (0);
	}
	else
	{
		//chdir(new_path);
		shell->cwd_int = 1;
		ft_printf(" going to new_path: %s and pwd %s\n", new_path, getenv("PWD"));
		shell->cwd = ft_str2join(get_prompt(shell), new_path);
		free(new_path);
		//shell->cwd = new_path;
	}
	return (1);
}

int cd(t_minishell *shell, char **arr)
{
	char	*home;

	home = getenv("HOME");
	if (!home || !arr || !*arr)
	{
		ft_printf("minishell: cd: HOME not set\n");
		return (1);
	}
	ft_printf("str: %s\n", *arr);
	if ((!ft_strncmp(*arr, "cd ~", ft_strlen(*arr)) || !ft_strncmp(*arr, "cd", ft_strlen(*arr))) && arr[1] == NULL)
	{
		ft_printf("home case\n");
		if (home == NULL)
			return (1);
		chdir(home);
		shell->cwd = home;
		shell->cwd_int = 1;
		return (1);
	}
	else if (arr[1])
	{
		if (new_path(shell, arr) == 0)
			return (0);
		return (1);
	}
	return (0);
}
