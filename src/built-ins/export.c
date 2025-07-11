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

char	*get_var_name(char *var)
{
	char	*eq;

	eq = ft_strchr(var, '=');
	if (eq)
		return (ft_strndup(var, eq - var));
	return (ft_strdup(var));
}

char	**check_vars(char **args)
{
	int		i;
	char	**vars;

	i = 1;
	vars = NULL;
	while (args[i])
	{
		if (valid_str(args[i]))
		{
			vars = add_str_to_array(vars, args[i]);
		}
		else
			ft_printf("shell: export: `%s': not a valid identifier\n", args[i]);
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
	new_env = ft_calloc(ft_len(shell->env) + 1, sizeof(char *));
	if (!new_env || !var)
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
	free_array(shell->env);
	return (new_env);
}

void	check_export(t_minishell *shell, char **vars)
{
	int		i;
	char	*full_var;
	char	*name;

	i = -1;
	if (!vars || !vars[0])
		return ;
	while (vars[++i])
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
	char	**vars;

	if (!args || !args[0])
		return (1);
	if (!args[1])
		return (print_export(shell));
	if (ft_len(args) > 1)
	{
		vars = check_vars(args);
		if (vars)
		{
			check_export(shell, vars);
			free_array(vars);
		}
	}
	return (1);
}
