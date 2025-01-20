/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 22:45:31 by gongarci          #+#    #+#             */
/*   Updated: 2025/01/16 23:20:06 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* static char	*add_var(t_minishell *shell, char *str)
{
	char	**new_env;

	new_env = add_str_to_array(shell->env, str);
	shell->env = new_env;
	return (NULL);
} */

// crear una function que separa el string en dos partes, la variable y el valor
// y luego llamar a add_var para agregarla al env
// si no hay valor, agregarla con valor NULL
// if  on str it has = it must be saved as a variable with a value
// if it doesn't have = it must be saved as a variable without a value

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

char	*check_var(char *str)
{
	int		i;
	char	*var;

	i = 0;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	var = ft_substr(str, 0, i);
	//check for quotes if it closes for ""  and test ' ' es missing;
	return (var);
}

void	ft_export(t_minishell *shell)
{
	char	*new_var;
	char	*str;
	int		i;

	i = 0;
	str = shell->prompt->str;
	ft_printf("export\n");
	new_var = ft_strchr(str, '='); //check for str if we have to add a new variable
	if (!ft_strncmp(str, "export", 6)) // nada que exportar
	{
		while(shell->env[i] != NULL)
			ft_printf("declare -x %s\n", shell->env[i++]);
		return ;
	}
/* 	else if (new_var != NULL) //exportar  variable sin valor
	{	
		add_var(shell, str);
	}
	else if (str) //exportar variable con valor
	{
		exportar una variable sin valor o varias variables con valor??
	} */
	return ;
}
