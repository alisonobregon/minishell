/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 21:04:39 by aliobreg          #+#    #+#             */
/*   Updated: 2025/04/09 21:40:07 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	find_position(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\'' || arg[i] == '"')
			break ;
		i++;
	}
	return (i);
}

int	get_arg_end(char *str, int end_index)
{
	char	**split;
	int		is_sp;
	int		is_sep;
	int		i;

	i = -1;
	split = ft_split("<< < >> > || | && &", ' ');
	if (!split)
		return (-1);
	is_sp = index_of_newline(str + end_index);
	while (split[++i])
	{
		is_sep = index_of(str + end_index, split[i], 1);
		if (is_sep < is_sp)
			return ((end_index + is_sep) + free_array(split));
	}
	return ((end_index + is_sp) + free_array(split));
}

int	handle_quotes(char *arg, int *quotes, char quotee, int *i)
{
	set_quotes(arg[*i], quotes);
	if (((arg[*i] == '\'' || arg[*i] == '\"') && quotee == arg[*i]))
		return (1);
	return (0);
}

char	*malloc_new_arg(char *arg, char **env, int lex)
{
	char	*new_arg;
	int		future_len;

	future_len = get_future_arglen(arg, env, lex);
	if (future_len == -1)
		return (NULL);
	new_arg = ft_calloc(future_len + 1, sizeof(char));
	if (!new_arg)
		return (NULL);
	return (new_arg);
}
