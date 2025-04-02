/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins-utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 23:16:22 by gongarci          #+#    #+#             */
/*   Updated: 2025/01/21 22:08:51 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_builtin(t_minishell *shell, char *cmd, char **args)
{
	if (!args || !shell->exec->args[0] || !shell->exec)
		return (-1);
	if (!ft_strncmp(cmd, "echo", 5) && ft_strlen(cmd) == 4)
		return (ft_echo(args));
	else if (!ft_strncmp(cmd, "cd", 3) && ft_strlen(cmd) == 2)
		return (cd(shell, args));
	else if (!ft_strncmp(cmd, "pwd", 4) && ft_strlen(cmd) == 3)
		return (pwd());
	else if (!ft_strncmp(cmd, "export", 7) && ft_strlen(cmd) == 6)
		return (ft_export(shell, args));
	else if (!ft_strncmp(cmd, "unset", 6) && ft_strlen(cmd) == 5)
		return (ft_unset(shell, args), 1);
	else if (!ft_strncmp(cmd, "env", 4) && !args[1])
		return (ft_env(shell));
	else if (!ft_strncmp(cmd, "exit", 5) && ft_strlen(cmd) == 4)
	{
		if (args[1])
			return (ft_exit(shell, ft_atol(args[1])), 1);
		else
			return (ft_exit(shell, 0), 1);
	}
	return (-1);
}

int	builtin_checker(t_minishell *shell, char *cmd)
{
	if (!shell->exec->args || !shell->exec->args[0] || !shell->exec)
		return (0);
	if (!ft_strncmp(cmd, "echo", 5))
		return (1);
	else if (!ft_strncmp(cmd, "cd", 3))
		return (1);
	else if (!ft_strncmp(cmd, "pwd", 4))
		return (1);
	else if (!ft_strncmp(cmd, "export", 7))
		return (1);
	else if (!ft_strncmp(cmd, "unset", 6))
		return (1);
	else if (!ft_strncmp(cmd, "env", 4) && !shell->exec->args[1])
		return (1);
	else if (!ft_strncmp(cmd, "exit", 5))
		return (1);
	return (0);
}

void	free_arrays(char **array1, char **array2)
{
	int	i;

	i = 0;
	if (!array1 || !array2)
		return ;
	if (*array1)
	{
		while (array1[i] != NULL)
			free(array1[i++]);
		if (array1)
			free(array1);
	}
	if (!array2)
		return ;
	if (*array2 && array2)
	{
		i = 0;
		while (array2[i] != NULL)
			free(array2[i++]);
		if (array2)
			free(array2);
	}
}

int	valid_str(char *str)
{
	int	i;

	i = 1;
	if (!str)
		return (0);
	if (ft_isalpha(str[0]) || str[0] == '_') // a valid str has to start with an alpha char or an underscore
	{
		while(str[i] != '\0')
		{
			if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_')
				return (0);
			i++;
		}
		return (1);
	}
	else
			return (0);
}
