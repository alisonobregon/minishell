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
	//t_exec	*tmp;

	while (*exec)
	{
		//tmp = (*exec)->next;
		free_array((*exec)->args);
		free_arrays((*exec)->infile, (*exec)->heredoc);
		if ((*exec)->outfile)
		{
			while ((*exec)->outfile)
			{
				if ((*exec)->outfile->file)
					free((*exec)->outfile->file);
				free((*exec)->outfile);
				(*exec)->outfile = (*exec)->outfile->next;
			}
		}
		free(*exec);
	}
	exit(0);
}
