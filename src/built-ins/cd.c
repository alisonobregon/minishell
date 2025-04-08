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

int	pwd(t_minishell *shell)
{
	char	*cwd;

	(void)shell;
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

void	set_pwd(t_minishell *shell, char *pwd)
{
	char	*nuevo;

	if (pwd == NULL)
	{
		perror("minishell: cd: error retrieving current directory");
		return ;
	}
	shell->env = rm_env_var(shell, "PWD");
	nuevo = ft_str2join("PWD=", pwd, 0, 1);
	shell->env = add_str_to_array(shell->env, nuevo);
	free(nuevo);
}

void	set_oldpwd(t_minishell *shell, char *oldpwd)
{
	char	*nuevo;

	if (oldpwd == NULL)
	{
		perror("minishell: cd: error retrieving current directory");
		return ;
	}
	shell->env = rm_env_var(shell, "OLDPWD");
	nuevo = ft_strjoin("OLDPWD=", oldpwd);
	shell->env = add_str_to_array(shell->env, nuevo);
	free(nuevo);
}

static int	new_path(t_minishell *shell, char **arr)
{
	char	*new_path;
	int		status;
	char	*oldpwd;

	new_path = ft_strdup(arr[1]);
	if (new_path == NULL)
	{
		ft_printf("minishell: cd: memory allocation error\n");
		return (-1);
	}
	oldpwd = getcwd(NULL, 0);
	new_path = ft_gnlstrjoin(new_path, "/", 1);
	status = chdir(new_path);
	if (status == -1)
	{
		ft_printf("minishell: cd: %s: No such file or directory\n", new_path);
		(free(new_path) , free(oldpwd));
		return (1);
	}
	set_oldpwd(shell, oldpwd);
	set_pwd(shell, getcwd(NULL, 0));
	shell->cwd = get_prompt(shell);
	if (oldpwd)
		free(oldpwd);
	return (free(new_path), 1);
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
		set_oldpwd(shell, getcwd(NULL, 0));
		set_pwd(shell, home);
		chdir(home);
		shell->cwd = get_prompt(shell);
		return (free(home), 1);
	}
	free(home);
	return (new_path(shell, arr));
}
