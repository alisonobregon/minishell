/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:15:18 by aliobreg          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/01/14 20:37:10 by gongarci         ###   ########.fr       */
=======
/*   Updated: 2025/01/16 21:39:27 by aliobreg         ###   ########.fr       */
>>>>>>> 2b0cb83a634fab2cca9401dc9b4326cc1754af77
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int get_quotes_end(char *str, int end)
{
	int end_index;
	
	end_index = -2; //por ahora no hay ninguna comilla
	if (str[0] == 39)
		end_index = get_
}
int get_end_index(char *str, int end)
{
	char	**split;
	int		end_index;

	split = ft_split("< << >> < | || & &&", ' ');
	if (!split)
		return(0);
	end_index = get_quotes_end(str, end)
	

	
}

int split_args(t_minishell *shell, char *str)
{
	int	i;
	int end_index;

	i = -1;
	while(str[++i])
	{
		if (str[i] == '\t' || str[i] == ' ')
			continue;
		if (str[i] == '>' || str[i] == '<' || str[i] == 34 || str[i] == 39 
		|| str[i] == '|' || str[i] == '&')
			end_index = get_end_index(str + i, -1);
	}
	
}
void parsing(t_minishell *shell)
{
	check_quotes(&(shell->prompt->str), 2, 2);
	//check_pipex
}