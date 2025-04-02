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
	if (!str)
		return (array);
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
	char	*pwd;
	int		i;
	int		len;

	i = 0;
	//Cambiado por Paula ;)
	if (!array || !*array)
		len = 1;
	else
		len = ft_len(array);
	copy = ft_calloc(len + 1, sizeof(char *));
	if (!copy)
		return (NULL);
	if (!array || !*array)
	{
		pwd = getcwd(NULL, 0);
		copy[0] = ft_strjoin("PWD=", pwd);
		printf("PWD=%s\n", copy[0]);
		copy[1] = NULL;
		return (copy);
	}
	while (array[i] != NULL)
	{
		copy[i] = ft_strdup(array[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

char	*ft_str2join(char *s1, char *s2, int f1, int f2)
{
	char	*substr;
	size_t	len;

	len = (ft_strlen(s1) + (ft_strlen(s2)) + 1);
	substr = (char *)ft_calloc(len, sizeof(char));
	if (!substr)
		return (NULL);
	else
	{
		ft_memcpy(substr, s1, ft_strlen(s1));
		ft_memcpy(substr + ft_strlen(s1), s2, ft_strlen(s2));
		substr[len - 1] = '\0';
	}
	if (f1)
		free(s1);
	if (f2)
		free(s2);
	return (substr);
}
