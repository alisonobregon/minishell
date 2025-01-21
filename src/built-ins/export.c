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
	int		len;

	if (ft_chrlen(str, '"') > 4 || ft_chrlen(str, 39) > 4) // in export just quotes for "expor" and all next variable are accepted
		return (0);
	if ((ft_chrlen(str, '"') % 2 ) != 0 || ((ft_chrlen(str, 39)) % 2 ) != 0)
		return (0);
	if (ft_strlen(str) < 6)
		return (0);
	export = ft_strnstr(str, "export", ft_strlen(str));
	ft_printf(" in just_export: %s\n", export);
	len = 7;
	ft_printf("result of strncmp %d\n", ft_strncmp(export, "export", len));
	if ((ft_chrlen(str, '"') % 2 ) != 0 || ((ft_chrlen(str, 39)) % 2 ) != 0)
		len--;
	if (!ft_strncmp(export, "export", len))
	{
		//free(export);
		return (1);
	}
	//free(export);
	return (0);
} 
// this function willl receive cmd = export  and the rest of the value
void	ft_export(t_minishell *shell)
{
	//char	*new_var;
	char	**args;
	char	*cmd;
	char	**tmp;
	char	*tmp2;
	int		i;
	int	quotes = 1;

	i = 0;
	tmp = NULL;
	ft_printf("inside of export\n");
	cmd = ft_strdup("export");
	args = ft_split(shell->prompt->str, ' ');
	ft_printf("just export aoutput %d\n", just_export(cmd));
	if (!ft_strncmp(cmd, "export", ft_strlen(cmd)) && ft_len(args) == 1) // nada que exportar, check for space before export
	{
		while(shell->env[i] != NULL)
			ft_printf("declare -x %s\n", shell->env[i++]);
		if (args)
			free_arrays(args, NULL);
		return ;
	}
	else if (ft_len(args) > 1 && !quotes) //exportar  variable sin valor
	{
		tmp = ft_arrjoin(shell->env, args);
		shell->env = tmp;
		free_arrays(args, NULL);
	}
	else if (ft_len(args) > 1 && quotes) //exportar  variable sin valor
	{
		tmp2 = ft_array_to_str(args);
		tmp = add_str_to_array(shell->env, tmp2);
		shell->env = tmp;
		free(tmp2);
		free_arrays(args, NULL);
	}
	if (args)
		free_arrays(args, NULL);
	return ;
}
