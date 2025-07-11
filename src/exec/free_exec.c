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

void	free_exec(t_exec **exec)
{
	t_exec	*temp;

	while (*exec)
	{
		temp = (*exec)->next;
		if ((*exec)->cmd)
			free((*exec)->cmd);
		if ((*exec)->args)
			free_array((*exec)->args);
		if ((*exec)->infile)
			free_array((*exec)->infile);
		if ((*exec)->outfile)
			free_output(&(*exec)->outfile);
		if ((*exec)->heredoc)
			free_array((*exec)->heredoc);
		free(*exec);
		(*exec) = temp;
	}
}

void	free_prompt(t_prompt **prompt)
{
	if (!prompt || !*prompt)
		return ;
	if ((*prompt)->str)
		free((*prompt)->str);
	free(*prompt);
}

void	free_child_shell(t_minishell **shell)
{
	if ((*shell)->env)
		free_array((*shell)->env);
	if ((*shell)->path)
		free_array((*shell)->path);
	if ((*shell)->prompt)
		free_prompt(&(*shell)->prompt);
	if ((*shell)->exec)
		free_exec(&((*shell)->exec));
	if ((*shell)->args)
		free_array((*shell)->args);
	if ((*shell)->cwd)
		free((*shell)->cwd);
	(*shell)->env = NULL;
	(*shell)->path = NULL;
	(*shell)->args = NULL;
	(*shell)->cwd = NULL;
	(*shell)->prompt = NULL;
	(*shell)->exec = NULL;
	free((*shell));
	*shell = NULL;
}

void	free_exec_node(t_exec **exec)
{
	t_exec	*temp;

	while (*exec)
	{
		temp = (*exec)->next;
		free((*exec)->cmd);
		if ((*exec)->args)
			free_array((*exec)->args);
		if ((*exec)->infile)
			free_array((*exec)->infile);
		if ((*exec)->outfile)
			free_output(&(*exec)->outfile);
		if ((*exec)->heredoc)
			free_array((*exec)->heredoc);
		free(*exec);
		*exec = temp;
	}
	*exec = NULL;
	exit(127);
}

int	command_list_clear(t_exec **command_list)
{
	t_exec	*temp;

	while (*command_list)
	{
		if ((*command_list)->next)
			temp = (*command_list)->next;
		free((*command_list)->cmd);
		if ((*command_list)->args)
			free_array((*command_list)->args);
		if ((*command_list)->infile)
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
