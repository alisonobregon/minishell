/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins-utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 23:16:22 by gongarci          #+#    #+#             */
/*   Updated: 2025/01/21 22:08:51 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_arrays(char **array1, char **array2)
{
	int	i;

	i = 0;
	if (array1)
	{
		while (array1[i] != NULL)
			free(array1[i++]);
		if (array1)
			free(array1);
	}
	if (array2)
	{
		i = 0;
		while (array2[i] != NULL)
			free(array2[i++]);
		if (array2)
			free(array2);
	}
}
