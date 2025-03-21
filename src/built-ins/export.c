/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 22:45:31 by gongarci          #+#    #+#             */
/*   Updated: 2025/01/21 22:26:59 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *get_var_name(char *var)
{
	char	*eq;

	eq = ft_strchr(var, '=');
	if (eq)
		return (ft_strndup(var, eq - var));
	return (ft_strdup(var));
}

int	index_array(char **array, char *str)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (!ft_strncmp(array[i], str, ft_strlen(array[i])))
			return (i);
		i++;
	}
	return (-1);
}

int	str_in_array(char **array, char *str)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		if (!ft_strcmp(array[i], str))
			return (1);
		i++;
	}
	return (0);
}

int	ft_chrlen(char *str, char c)
{
	int		i;
	int		counter;

	i = 0;
	counter = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			counter++;
		i++;
	}
	return (counter);
}

char	**check_vars(char **args)
{
	int		i;
	char	**vars;

	i = 1;
	vars = NULL;
	while (args[i])
	{
		if (ft_isalpha(args[i][0]) || args[i][0] == '_')
		{
			printf("times in check vars %d\n", i);
			vars = add_str_to_array(vars, args[i]);
		}
		else
			ft_printf("minishell: export: `%s': not a valid identifier\n", args[i]);
		i++;
	}
	return (vars);
}

char	**rm_env_var(t_minishell *shell, char *var)
{
	int		i;
	int		j;
	char	*var_name;
	char	**new_env;

	i = 0;
	j = 0;
	new_env = ft_calloc(ft_len(shell->env), sizeof(char *) + 1);
	if (!new_env)
		return (NULL);
	while (shell->env[i] != NULL)
	{
		var_name = get_var_name(shell->env[i]);
		if (ft_strcmp(var_name, var))
		{
			new_env[j] = ft_strdup(shell->env[i]);
			j++;
		}
		free(var_name);
		i++;
	}
	new_env[j] = NULL;
	free_arrays(shell->env, NULL);
	return (new_env);
}



void	check_export(t_minishell *shell, char **vars)
{
	int	i;
	char	*full_var;
	char	*name;
	i = -1;
	while(vars[++i])
	{
		full_var = vars[i];
		name = get_var_name(full_var);
		if (ft_strchr(full_var, '='))
		{
			shell->env = rm_env_var(shell, name);
			shell->env = add_str_to_array(shell->env, full_var);
		}
		else
		{
			if (!str_in_array(shell->env, name))
				shell->env = add_str_to_array(shell->env, full_var);
		}
		free(name);
	}
}

int	ft_export(t_minishell *shell, char **args)
{
	int		i;
	char	**vars;

	i = 0;
	ft_printf("inside of export\n");
	if (!args || !args[0])
	{
		ft_printf("inside of export null args\n");
		return (1);
	}
	if (!args[1])
	{
		while(shell->env[i] != NULL)
			ft_printf("declare -x ""%s""\n", shell->env[i++]);
		return (1);
	}
	if (ft_len(args) > 1)
	{
		vars = check_vars(args);
		check_export(shell, vars);
		free_arrays(vars, NULL);
	}
	return (1);
}
