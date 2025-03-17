/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:13:07 by marvin            #+#    #+#             */
/*   Updated: 2025/01/10 18:13:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int contains_only(char *str, int c)
{
	int i;

	i = -1;
	while(str[++i])
	{
		if (str[i] != c)
			return (0);
	}
	return (1);
}
char	*ft_array_to_str(char **array)
{
	char	*str;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (array[i] != NULL)
	{
		len += ft_strlen(array[i]);
		i++;
	}
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (array[i] != NULL)
	{
		ft_strlcat(str, array[i], len + 1);
		i++;
	}
	return (str);
}

char	**ft_arrjoin(char **arr1, char **arr2)
{
	char	**new_arr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_arr = ft_calloc(ft_len(arr1) + ft_len(arr2) + 1, sizeof(char *));
	if (!new_arr)
		return (NULL);
	while (arr1[i] != NULL)
	{
		new_arr[i] = ft_strdup(arr1[i]);
		i++;
	}
	while (arr2[j] != NULL)
	{
		new_arr[i] = ft_strdup(arr2[j]);
		i++;
		j++;
	}
	new_arr[i] = NULL;
	free_arrays(arr1, arr2);
	arr1 = NULL;
	arr2 = NULL;
	return (new_arr);
}

char	**add_str_to_array(char **array, char *str)
{
	char	**new_array;
	int		i;

	i = 0;
	if (!array)
	{
		new_array = ft_calloc(2, sizeof(char *));
		new_array[0] = ft_strdup(str);
		new_array[1] = NULL;
		return (new_array);
	}
	new_array = ft_calloc(ft_len(array) + 2, sizeof(char *));
	if (!new_array)
		return (NULL);
	while (array[i] != NULL)
	{
		new_array[i] = ft_strdup(array[i]);
		i++;
	}
	new_array[i] = ft_strdup(str);
	new_array[i + 1] = NULL;
	free_arrays(array, NULL);
	return (new_array);
}

char	**strarray_copy(char **array)
{
	char	**copy;
	int		i;

	i = 0;
	if (!array || !*array)
		return (NULL);
	copy = ft_calloc(ft_len(array) + 1, sizeof(char *));
	if (!copy)
		return (NULL);
	while (array[i] != NULL)
	{
		copy[i] = ft_strdup(array[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
