/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 20:38:09 by gongarci          #+#    #+#             */
/*   Updated: 2025/02/26 21:30:18 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


void	ft_env(t_minishell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strchr(shell->env[i], '='))
			ft_printf("%s\n", shell->env[i]);
		i++;
	}
}
