/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 22:00:27 by marvin            #+#    #+#             */
/*   Updated: 2025/04/05 22:00:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_exec	*exec_lstlast(t_exec *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	get_arg_type(char *str)
{
	if (!ft_strncmp(str, ">>", 2) || !ft_strncmp(str, "<<", 2)
		|| !ft_strncmp(str, "<", 1) || !ft_strncmp(str, ">", 1) \
		|| !ft_strncmp(str, "&", 1))
		return (1);
	else if (!ft_strncmp(str, "|", 1))
		return (2);
	else if (!ft_strncmp(str, "||", 2))
		return (3);
	else if (!ft_strncmp(str, "&&", 2))
		return (4);
	return (0);
}

int	index_of(char *str, char *search, int n)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (ft_strncmp(str + i, search, ft_strlen(search)) == 0)
			n--;
		if (n <= 0)
			break ;
	}
	return (i);
}

int	index_of_newline(char *str)
{
	int	index;
	int	temp;

	index = index_of(str, " ", 1);
	temp = index_of(str, "\t", 1);
	if (temp || str[0] == '\t')
		if (temp < index)
			index = temp;
	return (index);
}

t_exec	*exec_new(void)
{
	t_exec	*new;

	new = ft_calloc(1, sizeof(t_exec));
	if (!new)
		return (NULL);
	new->args = NULL;
	new->cmd = NULL;
	new->infile = NULL;
	new->heredoc = NULL;
	new->outfile = NULL;
	new->todo_next = 0;
	new->next = NULL;
	return (new);
}
