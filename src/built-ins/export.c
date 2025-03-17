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
	int	i;
	char	**vars;
	i = 0;
	vars = NULL;
	while(args[i])
	{
		if (ft_isalpha(args[i][0]) || args[i][0] == '_')
		{
			printf("times in check vars %d\n", i + 1);
			vars = add_str_to_array(vars, args[i]);
		}
		else
			ft_printf("minishell: export: `%s': not a valid identifier\n", args[i]);
		i++;
	}
	return (vars);
}


int	ft_export(t_minishell *shell, char **args)
{
	int		i;
	char	**vars;

	i = 0;
	ft_printf("inside of export\n");
	if (!ft_strncmp(args[0], "export", 7) && !args[1]) // nada que exportar, check for space before export
	{
		while(shell->env[i] != NULL)
			ft_printf("declare -x %s\n", shell->env[i++]);
		return (1);
	}
	if (ft_len(args) > 1)
	{
		vars = check_vars(args);
		printf("before check vars \n");
		shell->env = ft_arrjoin(shell->env, vars);
	}
	return (1);
}
