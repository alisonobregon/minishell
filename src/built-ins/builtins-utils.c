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
		return (pwd(shell));
	else if (!ft_strncmp(cmd, "export", 7) && ft_strlen(cmd) == 6)
		return (ft_export(shell, args));
	else if (!ft_strncmp(cmd, "unset", 6) && ft_strlen(cmd) == 5)
		return (ft_unset(shell, args), 1);
	else if (!ft_strncmp(cmd, "env", 4) && !args[1])
		return (ft_env(shell));
	else if (!ft_strncmp(cmd, "exit", 5) && ft_strlen(cmd) == 4)
		return (ft_exit(shell, args), 1);
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
	free_array(array1);
	free_array(array2);
}

int	valid_str(char *str)
{
	int	i;

	i = 1;
	if (!str)
		return (0);
	if (ft_isalpha(str[0]) || str[0] == '_')
	{
		while (str[i] != '\0')
		{
			if (!ft_isalnum(str[i]) && str[i] != '_'
				&& str[i] != '=' && str[i] != ' ' && str[i] != '-')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

int	print_export(t_minishell *shell)
{
	int		i;
	char	chr;

	i = 0;
	chr = 'A';
	while ((chr >= 'A' && chr <= 'Z' ) || (chr >= 'a' && chr <= 'z'))
	{
		while (shell->env[i] != NULL && shell->env[i][0] == chr)
			ft_printf("declare -x ""%s""\n", shell->env[i++]);
		if (shell->env[i] == NULL)
		{
			i = 0;
			chr++;
			if (chr == 'Z')
				chr = 'a';
		}
		else
			i++;
	}
	return (1);
}
