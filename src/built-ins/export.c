/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 22:45:31 by gongarci          #+#    #+#             */
/*   Updated: 2025/01/20 21:56:26 by gongarci         ###   ########.fr       */
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

/* char	*check_var(char *str)
{
	int		i;
	char	*var;

	i = 0;
	//if (ft_chrlen(str))
	//check for quotes if it closes for ""  and test ' ' es missing;
	//if we found quotes in export it has to count, if we found quotes in str it has to be counter
	// as just one variable with all text inside
	// if there are  many of them, it has to be separated in different variables
	return (var);
} */

int	just_export(char *str)
{
	char	*export;

	if (ft_chrlen(str, '"') > 4 || ft_chrlen(str, 39) > 4)
		return (0);
	if ((ft_chrlen(str, '"') % 2 ) != 0 && (ft_chrlen(str, 39) % 2 ) != 0)
		return (0);
	if (ft_strlen(str) < 6)
		return (0);
	export = ft_strnstr(str, "export", ft_strlen(str));
	ft_printf("export: %s\n", export);
	if (ft_strncmp(export, "export", ft_strlen(export) - 1))
	{
		free(export);
		return (0);
	}
	free(export);
	return (1);
} 

void	ft_export(t_minishell *shell)
{
	//char	*new_var;
	char	*str;
	int		i;

	i = 0;
	str = shell->prompt->str;
	ft_printf("export\n");
	//new_var = ft_strchr(str, '='); //check for str if we have to add a new variable
	//check_var(str);
	ft_printf("%d\n", ft_len(ft_split(str, ' ')));
	if (!(ft_strncmp(str, "export", 6)) || (just_export(str)) == 1) // nada que exportar, check for space before export
	{
		while(shell->env[i] != NULL)
			ft_printf("declare -x %s\n", shell->env[i++]);
		return ;
	}
	/* else if (new_var != NULL) //exportar  variable sin valor
	{	
		add_var(shell, str);
	} */
	/*else if (str) //exportar variable con valor
	{
		exportar una variable sin valor o varias variables con valor??
	} */
	return ;
}
