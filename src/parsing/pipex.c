/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliobreg <aliobreg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:22:45 by aliobreg          #+#    #+#             */
/*   Updated: 2025/01/16 19:41:15 by aliobreg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"



int ft_countpipes(char *str)
{
	int i;
	int res;
	char quote;
		
	i = -1;
	res = 0;
	while (str[++i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
		quote = str[i];
		i++;
		while(str[i] && str[i] != quote)
			i++;
		}
		if ((str[i] == '|' && (str[i + 1] == '|' || str[i + 1] == '\0' || ft_blank(str[i + 1]) != 1)) || str[0] == '|')
			ft_printf("syntax error near unexpected token '|'");
		if (s[i] == '|')
			res++;
	}
	return(res);
}
