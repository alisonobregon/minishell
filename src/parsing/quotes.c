/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 20:53:36 by aliobreg          #+#    #+#             */
/*   Updated: 2025/04/09 21:40:15 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	set_quotes(char c, int *quotes)
{
	int	c_quotes;

	c_quotes = *quotes;
	if (c == '\'')
	{
		if (c_quotes == 0)
			*quotes = 1;
		else if (c_quotes == 1)
			*quotes = 0;
	}
	if (c == '\"')
	{
		if (c_quotes == 0)
			*quotes = 2;
		else if (c_quotes == 2)
			*quotes = 0;
	}
	return (c_quotes);
}

int	get_future_arglen(char *arg, char **env, int lex)
{
	int		i;
	int		quotes;
	int		len;
	char	*var_val;

	i = 0;
	len = 0;
	quotes = 0;
	while (arg[i])
	{
		if (set_quotes(arg[i], &quotes) == quotes)
			len++;
		if (quotes != 1 && arg[i] == '$')
		{
			var_val = get_env(arg + i, env, lex);
			if (!var_val)
				return (-1);
			len += ft_strlen(var_val) - 1;
			free(var_val);
			i += get_env_len(arg + i) - 1;
		}
		i++;
	}
	return (len);
}

/* int	find_position(char *arg)
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
} */

char	*replace_env(char *arg, char **env, int last_exit, t_env *envi)
{
	int	quotes;
	int	n_args;
	int	i;

	quotes = 0;
	n_args = 0;
	i = -1;
	envi->new_arg = malloc_new_arg(arg, env, last_exit);
	while (arg[++i])
	{
		if (handle_quotes(arg, &quotes, envi->quotee, &i) == 1)
			continue ;
		if (quotes != 1 && arg[i] == '$')
		{
			envi->var_val = get_env(arg + i, env, last_exit);
			replace_var(envi->var_val, envi->new_arg, &n_args);
			i += get_env_len(arg + i) - 1;
		}
		else
			envi->new_arg[n_args++] = arg[i];
	}
	return (envi->new_arg);
}

int	replace_var(char *arg, char *new_args, int *n_args)
{
	if (!arg)
		return (free_array(&new_args));
	*n_args += ft_strcat(new_args + (*n_args), arg);
	free(arg);
	return (1);
}

int	replace_quotes(char ***args, char **env, int last_exit)
{
	char	**new_args;
	t_env	*envi;
	int		i;

	i = 0;
	if (!args || !*args)
		return (0);
	envi = ft_calloc(1, sizeof(t_env));
	new_args = ft_calloc(ft_len(*args) + 1, sizeof(char *));
	if (!new_args)
		return (0);
	while ((*args)[i])
	{
		envi->quotee = (*args)[i][find_position((*args)[i])];
		new_args[i] = replace_env((*args)[i], env, last_exit, envi);
		i++;
	}
	new_args[i] = NULL;
	free_array(*args);
	*args = new_args;
	free(envi);
	return (1);
}

/*
char *replace_env(char *arg, char **env, int last_exit)
{
	int i;
	int quotes;
	int n_args;
	char *new_arg;
	char *var_val;
	char quotee;

	i = -1;
	quotes = 0;
	n_args = 0;
	new_arg = malloc_new_arg(arg, env, last_exit);
	if (!new_arg)
		return (NULL);
	quotee = arg[0];
	while (arg[++i])
	{
		set_quotes(arg[i], &quotes);
		if (((arg[i] == '\''|| arg[i] == '\"')  && quotee == arg[i]))
			continue;
		if (quotes == 1)
		{
			new_arg[n_args++] = arg[i];
			continue;
		}
		if (quotes != 1 && arg[i] == '$')
		{
			var_val = get_env(arg + i, env, last_exit);
			if (!(replace_var(var_val, new_arg, &n_args)))
				return (NULL);
			i += get_env_len(arg + i) - 1;
		}
		else
			new_arg[n_args++] = arg[i];
	}
	new_arg[n_args] = 0;
	return (new_arg);
}
*/