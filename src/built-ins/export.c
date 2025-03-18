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

//this function should check if the array of vars has any repeated variables on shell->env and if it does,
//it should replace the value of the variable
void	check_repeats(t_minishell *shell, char **var)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (var[i])
	{
		while (shell->env[j])
		{
			if (!ft_strncmp(var[i], shell->env[j], ft_strlen(var[i]))
				&& shell->env[j][ft_strlen(var[i])] == '=')
			{
				free(shell->env[j]);
				shell->env[j] = ft_strdup(var[i]);
				var = rm_str_from_array(var, var[i]);
				print_array(shell->env);
				print_array(var);
				i = 0;
				break;
			}
			j++;
		}
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
	if (!ft_strncmp(args[0], "export", 7) && !args[1]) // nada que exportar, check for space before export
	{
		while(shell->env[i] != NULL)
			ft_printf("declare -x %s\n", shell->env[i++]);
		return (1);
	}
	if (ft_len(args) >= 1)
	{
		vars = check_vars(args);
		check_repeats(shell, vars);
		printf("before check vars \n");
		shell->env = ft_arrjoin(shell->env, vars);
	}
	return (1);
}
