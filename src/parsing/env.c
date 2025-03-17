/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliobreg <aliobreg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 20:30:42 by aliobreg          #+#    #+#             */
/*   Updated: 2025/03/17 21:42:58 by aliobreg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int env_name_len(char *env_name)
{
	int i;

	i = 0;
	while (env_name[i] && env_name[i] != '=')
		i++;
	return (i);
}
char *get_env(char *env_name, char **env, int last_exit)
{
	int i;
	char *s_pid;

	i = -1;
	s_pid = getenv("PID");
	printf("s_pid: %s\n", s_pid);
	if (env_name[1] == '?')
		return (ft_itoa(last_exit));
	else if (contains_only(env_name, '$'))
		return (ft_strdup(env_name));
	else if (env_name[1] == '$')
		return (ft_strdup(s_pid));
	else if (env_name[1] == '\'' || env_name[1] == '\"')
		return (ft_strdup("$"));
	else if (!ft_isalpha(env_name[1]))
		return (ft_strdup(""));
	while (env[++i])
	{
		if (!(ft_strncmp(env[i], env_name + 1, env_name_len(env[i]))))
			return (ft_strdup(env[i] + get_env_len(env_name)));
	}
	return (ft_strdup(""));
} 

int get_env_len(char *str)
{
	int i;
	int num;

	i = 0;
	if (contains_only(str, '$'))
		return (ft_strlen(str));
	if (!ft_strncmp(str, "?", 1))
		return (1);
	num = 0;
	if (ft_isdigit(str[1]))
		num = 1;
	while (str[i] || (i == 0 && str[i] == '$'))
	{
		if ((num && (ft_isalpha(str[i]) || str[i] == '_')))
			return (i);
		if (!ft_isalnum(str[i]) && str[i] != '_' && i != 0)
			return (i);
		i++;
	}
	return (i);
}
