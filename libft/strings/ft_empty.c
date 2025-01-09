/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_empty.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 20:56:26 by gongarci          #+#    #+#             */
/*   Updated: 2024/08/21 15:25:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_empty(char *argv)
{
	int	len;

	len = ft_strlen(argv);
	if (argv[0] == '\0' || len == 0)
		return (1);
	else if (len > 0 && ft_strncmp(argv, " ", len) != 0)
		return (0);
	else
		return (1);
}
