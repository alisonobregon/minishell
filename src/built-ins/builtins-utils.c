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

int is_builtin(t_exec *exec)
{
	
	if (!ft_strncmp(exec->cmd, "echo", 5))
		return(ft_echo(exec->args));
	if (!ft_strncmp(exec->cmd, "cd", 3))
		return (1);
	if (!ft_strncmp(exec->cmd, "pwd", 4))
		return(pwd());
	if (!ft_strncmp(exec->cmd, "export", 7))
		return (1);
	if (!ft_strncmp(exec->cmd, "unset", 6))
		return (1);
	if (!ft_strncmp(exec->cmd, "env", 4))
		return (1);
	if (!ft_strncmp(exec->cmd, "exit", 5))
		return (1);
	return (0);
}
int ft_exit(t_minishell *shell)
{
	(void)shell;
	exit(0);
	return (0);
}
void	free_arrays(char **array1, char **array2)
{
	int	i;

	i = 0;
	if (array1)
	{
		while (array1[i] != NULL)
			free(array1[i++]);
		if (array1)
			free(array1);
	}
	if (array2)
	{
		i = 0;
		while (array2[i] != NULL)
			free(array2[i++]);
		if (array2)
			free(array2);
	}
}
