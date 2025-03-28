/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 00:48:06 by marvin            #+#    #+#             */
/*   Updated: 2025/03/10 00:48:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_exec_node(t_exec **exec)
{
	t_exec	*temp;

	while (*exec)
	{
		temp = (*exec)->next;
		free((*exec)->cmd);
		if((*exec)->args)
			free_array((*exec)->args);
		if((*exec)->infile)
			free_array((*exec)->infile);
		if ((*exec)->outfile)
			free_output(&(*exec)->outfile);
		if ((*exec)->heredoc)
			free_array((*exec)->heredoc);
		free(*exec);
		*exec = temp;
	}
	*exec = NULL;
	exit(0);
}

int command_list_clear(t_exec **command_list)
{
	t_exec	*temp;

	while (*command_list)
	{
		if ((*command_list)->next)
			temp = (*command_list)->next;
		free((*command_list)->cmd);
		if((*command_list)->args)
			free_array((*command_list)->args);
		if((*command_list)->infile)
			free_array((*command_list)->infile);
		if ((*command_list)->outfile)
			free_output(&(*command_list)->outfile);
		if ((*command_list)->heredoc)
			free_array((*command_list)->heredoc);
		free(*command_list);
		*command_list = temp;
	}
	*command_list = NULL;
	return (0);
}

int free_output(t_output **output)
{
	t_output	*temp;

	while (*output)
	{
		temp = (*output)->next;
		free((*output)->file);
		free(*output);
		*output = temp;
	}
	*output = NULL;
	return (0);
}

int free_shell(t_minishell *shell)
{
	int exit_status;

	exit_status = shell->status;
	if (shell->prompt)
	{
		if (shell->prompt->str)
			free(shell->prompt->str);
		if (shell->prompt->cwd)
			free(shell->prompt->cwd);
		free(shell->prompt);
	}
	if (shell->exec)
		command_list_clear(&(shell->exec));
	if (shell->env)
		free_array(shell->env);
	printf("paaaaaaaa\n");
	/*if(shell->args)
		free_array(shell->args);*/ //seguro que ya lo libere antes :)))))
	if (shell)
		free(shell);
	return (exit_status);
}
