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

void	ft_exit(t_minishell *shell, long status)
{
	if (status >= LONG_MAX)
	{
		ft_printf("bash: exit: %ld: numeric argument required\n", status);
		free_child_shell(shell);
		exit(2);
	}
	if (status > 255)
		status = status % 256;
	ft_printf("exit\n");
	free_child_shell(shell);
	exit(status);
}
