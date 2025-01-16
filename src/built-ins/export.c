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

char	*add_var(t_minishell *shell, char *str)
{
	char	**new_env;

	new_env = ft_calloc(ft_len(shell->env) + 2, sizeof(char *));
	if (!new_env)
		return (NULL);
	
}
void	ft_export(t_minishell *shell)
{
	char	*new_var;
	char	*str;

	str = shell->prompt->str;
	ft_printf("export\n");
	if (!ft_strncmp(str, "export", ft_strlen(str))) // nada que exportar
	{
		//ft_putstr_fd("export: not an identifier\n", 2);
		ft_env(shell);
		return ;
	}
	else if (str) //exportar  variable sin valor
	{	
		
	}
	else if (str) //exportar variable con valor
	{
		
	}
	return ;
}
