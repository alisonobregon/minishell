/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 19:09:50 by gongarci          #+#    #+#             */
/*   Updated: 2024/07/25 18:34:35 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_gnlmemset(void *b, int c, size_t len)
{
	char	*p;

	p = (char *)b;
	while (len > 0)
	{
		p[len - 1] = c;
		len--;
	}
	return (b);
}

int	ft_gnlstrlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	*ft_gnlmemcpy(void *dest, const void *src, size_t bytes)
{
	char	*p_dest;
	char	*p_src;
	size_t	i;

	if (!dest || !src)
		return (NULL);
	i = 0;
	p_dest = (char *)dest;
	p_src = (char *)src;
	while (i < bytes)
	{
		p_dest[i] = p_src[i];
		i++;
	}
	return (dest);
}

/*char	*ft_gnlstrdup(const char *str)
{
	char	*point;
	size_t	len;

	len = ft_strlen(str);
	point = (char *)malloc(sizeof(*point) * (len + 1));
	if (!point)
		return (NULL);
	ft_memcpy(point, str, len + 1);
	return (point);
}*/

char	*ft_gnlstrjoin(char *s1, char *s2, int len2)
{
	char	*substr;
	int		len1;
	int		sub_len;

	len1 = ft_gnlstrlen(s1);
	if (!s1 || !s2)
		return (NULL);
	sub_len = (len1 + len2 + 1);
	substr = malloc(sub_len);
	if (!substr)
		return (NULL);
	else
	{
		ft_gnlmemcpy(substr, s1, len1);
		ft_gnlmemcpy(substr + len1, s2, len2);
		substr[sub_len -1] = '\0';
	}
	free(s1);
	return (substr);
}
