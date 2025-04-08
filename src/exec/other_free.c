/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliobreg <aliobreg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 20:41:41 by aliobreg          #+#    #+#             */
/*   Updated: 2025/04/08 20:43:08 by aliobreg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	free_output(t_output **output)
{
	t_output	*temp;

	if (!output || !*output)
		return (0);
	while (*output)
	{
		temp = (*output)->next;
		if ((*output)->file)
			free((*output)->file);
		free(*output);
		*output = temp;
	}
	*output = NULL;
	return (0);
}

int	free_shell(t_minishell *shell)
{
	int exit_status;

	exit_status = shell->status;
	if (shell->prompt)
	{
		if (shell->prompt->str)
			free(shell->prompt->str);
		free(shell->prompt);
	}
	if (shell->exec)
		command_list_clear(&(shell->exec));
	if (shell->env)
	{
		if (shell->path)
			free_array(shell->path); 
		free_array(shell->env);
	}
	if (shell)
		free(shell);
	return (exit_status);
}
