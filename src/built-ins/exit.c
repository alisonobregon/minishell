/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliobreg <aliobreg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 20:36:09 by gongarci          #+#    #+#             */
/*   Updated: 2025/03/31 20:01:51 by aliobreg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_bigger_than_long(const char *str)
{
	int			i;
	long long	result;

	i = 0;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || (str[i] == '+'))
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > (str[i] - '0') + (result * 10))
			return (1);
		result = (str[i] - '0') + (result * 10);
		i++;
	}
	return (0);
}

long long	check_exit_args(char **args)
{
	int	i;

	i = 0;
	if (!args[1])
		return (0);
	if (ft_len(args) > 2)
		return (ft_printf("exit \nbash: exit: too many arguments\n"), -1);
	while (args[1][i])
	{
		if (!ft_isdigit(args[1][i++]) && args[1][0] != '-' && args[1][0] != '+')
		{
			ft_printf("exit\n");
			ft_printf("bash: exit: %s: numeric argument required\n", args[1]);
			return (2);
		}
	}
	return (ft_atol(args[1]));
}

void	ft_exit(t_minishell *shell, char **args)
{
	long long	status;

	status = 0;
	status = check_exit_args(args);
	if (status == -1)
		return ;
	if (args[1] && is_bigger_than_long(args[1]))
	{
		ft_printf("exit\n");
		ft_printf("bash: exit: %s: numeric argument required\n", args[1]);
		free_child_shell(&shell);
		exit(2);
	}
	status = status % 256;
	ft_printf("exit\n");
	free_child_shell(&shell);
	exit(status);
}
