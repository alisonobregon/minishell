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

int is_builtin(t_minishell *shell, char *cmd)
{
	if (!shell->exec->args || !shell->exec->args[0] || !shell->exec)
		return (0);
	if (shell->exec->infile || shell->exec->outfile)
	{
		if (!fd_checker(&shell->exec))
			return (1);
	}
	if (!ft_strncmp(cmd, "echo", 5))
		return (ft_echo(shell->exec->args));
	else if (!ft_strncmp(cmd, "cd", 3))
		return (cd(shell, shell->exec->args));
	else if (!ft_strncmp(cmd, "pwd", 4))
		return (pwd());
	else if (!ft_strncmp(cmd, "export", 7) && !shell->exec->todo_next)
		return (ft_export(shell, shell->exec->args));
	else if (!ft_strncmp(cmd, "unset", 6))
		return (ft_unset(shell, shell->exec->args), 1);
	else if (!ft_strncmp(cmd, "env", 4) && !shell->exec->args[1])
		return (ft_env(shell));
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
