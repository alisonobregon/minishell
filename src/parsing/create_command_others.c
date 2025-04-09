/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_others.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliobreg <aliobreg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 20:58:14 by aliobreg          #+#    #+#             */
/*   Updated: 2025/04/09 21:22:48 by aliobreg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	str_array_append(char ***array, char *str)
{
	char	**new;
	int		i;

	i = 0;
	new = ft_calloc(sizeof(char *), ft_strarr_len(*array) + 2);
	if (!new)
		return (print_and_return("no memory allocated", NULL, 0));
	if ((*array))
	{
		while ((*array)[i])
		{
			new[i] = ft_strdup((*array)[i]);
			if (!new[i])
				return (0);
			i++;
		}
	}
	new[i] = ft_strdup(str);
	if (!new[i])
		return (0);
	if (*array)
		free_array(*array);
	new[i + 1] = NULL;
	*array = new;
	return (1);
}

int	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array[i])
		return (0);
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (0);
}

void	new_cmd_asign(t_exec *new)
{
	if (get_arg_type(new->cmd) == 1 && new->args)
		new->cmd = ft_strdup(new->args[0]);
	if (new->cmd)
		new->cmd = quit_quotes(new->cmd);
}

char	*quit_quotes(char *argument)
{
	char	*tmp;
	char	*new_arg;

	tmp = NULL;
	if (!argument)
		return (NULL);
	if (argument[0] == '\'')
	{
		tmp = ft_strdup(argument);
		new_arg = ft_strtrim(tmp, "'");
		free(tmp);
		free(argument);
		return (new_arg);
	}
	if (argument[0] == '\"')
	{
		tmp = ft_strdup(argument);
		new_arg = ft_strtrim(tmp, "\"");
		free(tmp);
		free(argument);
		return (new_arg);
	}
	return ((argument));
}
