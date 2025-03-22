/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 20:35:54 by gongarci          #+#    #+#             */
/*   Updated: 2025/03/18 20:58:22 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**rm_str_from_array(char **array, char *str)
{
	char	**new_array;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_array = ft_calloc(ft_len(array), sizeof(char *));
	if (!new_array)
		return (NULL);
	while (array[i] != NULL)
	{
		if (ft_strncmp(array[i], str, ft_strlen(str)) != 0)
		{
			new_array[j] = ft_strdup(array[i]);
			j++;
		}
		i++;
	}
	new_array[j] = NULL;
	free_arrays(array, NULL);
	return (new_array);
}
