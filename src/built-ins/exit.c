/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 20:36:09 by gongarci          #+#    #+#             */
/*   Updated: 2025/03/21 20:43:10 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exit_shell(t_minishell *shell, long status)
{
	if (status >= LONG_MAX)
	{
		ft_printf("bash: exit: %ld: numeric argument required\n", status);
		free_shell(shell);
		exit(2);
	}
	if (status > 255)
		status = status % 256;
	free_shell(shell);
	exit(status);
}
