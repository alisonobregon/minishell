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
		/* if (ft_strncmp(array[i], str, ft_strlen(array[i])) == 0)
			return (1); */
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

void	check_repeats(t_minishell *shell, char **var)
{
	int		i;
	int		j;
	int		k;
	//int		index;

	i = 0;
	while (var[i])
	{
		j = 0;
		k = 0;
		while (shell->env[j])
		{
			if (!ft_strncmp(shell->env[j], var[i], ft_strlen(shell->env[j])))
			{
				if (!ft_strcmp(shell->env[j], var[i]) || !ft_strchr(var[i], '='))
					break;
				if (ft_strlen(shell->env[j]) >= ft_strlen(var[i]))
					break;
				free(shell->env[j]);
				shell->env[j] = ft_strdup(var[i]);
				var = rm_str_from_array(var, var[i]);
				k = i;
				i = -1;
				break;
			}
			j++;
			if (str_in_array(shell->env, var[i]))
			{
				if (ft_strchr(var[i], '='))
					var = rm_str_from_array(var, var[i]);
				else
					i++;
			}
		}
		shell->env = add_str_to_array(shell->env, var[k]);
		i++;
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
	if (!ft_strncmp(args[0], "export", 7) && !args[1])
	{
		while(shell->env[i] != NULL)
			ft_printf("declare -x %s\n", shell->env[i++]);
		return (1);
	}
	if (ft_len(args) >= 1)
	{
		vars = check_vars(args);
		check_repeats(shell, vars);
		free_arrays(vars, NULL);
		print_array(shell->env);
	}
	return (1);
}
