/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliobreg <aliobreg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 21:04:39 by aliobreg          #+#    #+#             */
/*   Updated: 2025/04/08 21:06:06 by aliobreg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
