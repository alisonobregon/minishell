/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:22:11 by gongarci          #+#    #+#             */
/*   Updated: 2024/07/15 20:18:41 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strldup(const char *str, int size)
{
	char	*point;
	int		len;
	
	len = ft_strlen(str);
	if (len > size)
		len = size;
	point = ft_calloc(sizeof(char), len + 1);
	if (!point)
		return (NULL);
	while (--len > -1)
		point[len] = str[len];
	printf("valor de point es %s\n", point);
	return (point);
}

/*int	main(void)
{
	char	*str;

	str = ft_strdup("Hello World");
	printf("valor de str es %s\n", str);
	return (0);
}*/
