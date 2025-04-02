/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:34:19 by aliobreg          #+#    #+#             */
/*   Updated: 2025/03/31 16:21:34 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*le paso los argumentos y la idea principal es imprimirlo con printfd*/
void	echo_args(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (ft_strncmp(str + i, "\n", 2) == 0)
		{
			ft_putchar_fd('\n', 1);
			continue ;
		}
		else
			ft_putchar_fd(str[i], 1);
	}
}

int	ft_echo(char **args)
{
	int	i;
	int	n_flag;

	i = 0;
	n_flag = 0;
	if (args[1] && !ft_strncmp(&args[1][0], "-", 1))
	{
		if (!ft_strncmp(&args[1][1], "n", 1))
		{
			n_flag = 1;
			i++;
		}
	}
	while (args[++i])
	{
		if ((!n_flag && i > 1) || (n_flag && i > 2))
			ft_putchar_fd(' ', 1);
		echo_args(args[i]);
	}
	if (!n_flag)
		ft_putchar_fd('\n', 1);
	return (0);
}
