/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliobreg <aliobreg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 20:30:42 by aliobreg          #+#    #+#             */
/*   Updated: 2025/04/08 21:03:50 by aliobreg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	env_name_len(char *env_name)
{
	int	i;

	i = 0;
	while (env_name[i] && env_name[i] != '=')
		i++;
	return (i);
}

char	*get_env(char *env_name, char **env, int last_exit)
{
	int	i;

	i = -1;
	if (env_name[1] == '?')
		return (ft_itoa(last_exit));
	else if (contains_only(env_name, '$'))
		return (ft_strdup(env_name));
	else if (env_name[1] == '$' || env_name[1] == '/' || env_name[1] == '.'
		|| env_name[1] == ':' || env_name[1] == 45 || env_name[1] == '!'
		|| env_name[1] == '@' || env_name[1] == '#' || env_name[1] == '%'
		|| env_name[1] == '^' || env_name[1] == '&' || env_name[1] == '*')
		return (ft_strdup("$"));
	else if (env_name[1] == '/')
		return (ft_strdup("/"));
	else if (env_name[1] == '\'' || env_name[1] == '\"')
		return (ft_strdup("$"));
	else if (!ft_isalpha(env_name[1]) && env_name[1] != '_')
		return (ft_strdup(""));
	while (env[++i])
	{
		if ((ft_strncmp(env[i], env_name + 1, env_name_len(env[i])) == 0)
			&& env[i][get_env_len(env_name + 1)] == '=')
			return (ft_strdup(env[i] + get_env_len(env_name)));
	}
	return (ft_strdup(""));
}

int	get_env_len(char *str)
{
	int	i;
	int	num;

	i = 0;
	if (contains_only(str, '$'))
		return (ft_strlen(str));
	if (!ft_strncmp(str, "$?", 2))
		return (2);
	num = ft_isdigit(str[1]);
	while (str[++i])
	{
		if ((num && !ft_isdigit(str[i])))
			return (i);
		if (!num && !ft_isalnum(str[i]) && str[i] != '_')
			return (i);
	}
	return (i);
}

size_t	ft_strcat(char *dest, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (i);
}
