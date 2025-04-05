/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliobreg <aliobreg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:18:14 by aliobreg          #+#    #+#             */
/*   Updated: 2025/02/11 20:43:26 by aliobreg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


int check_other_quote(char **buf, int *i, char c)
{
	int	n;
		
	n = 1;
	while((*buf)[*i + 1] && (*buf)[*i + 1] != c)
		(*i)++;
	if ((*buf)[*i + 1] == c)
	{
		n++;
		(*i)++;
	}
	return (n);

}

int	check_quotes(char **buf, int simple_quote, int double_quote)
{
	int	i;
	char *temp;
	char *temp2;
	char *dquote;

	i = -1;
	while ((*buf)[++i])
	{
		if ((*buf)[i] == 34)
			double_quote += check_other_quote(buf, &i, (*buf)[i]);
		if ((*buf)[i] == 39)
			simple_quote += check_other_quote(buf, &i, (*buf)[i]);
	}
	if (((double_quote % 2 != 0) || (simple_quote % 2 != 0)) && !g_sigint)
	{
		other_signals();
		dquote = readline("dquote>");
		if (!dquote || g_sigint)
		{
			ft_printf("Error quotes don't close\n");
			free(*buf);
			return (1);
		}
		temp = ft_strjoin(*buf, "\n");
		temp2 = ft_strjoin(temp, dquote);
		free(temp);
		free(dquote);
		free(*buf);
		*buf = temp2;
		return (check_quotes(buf, 0, 0));		
	}
	wait_signal();
	return (2);
}
int free_return(char **buf)
{
	if (buf)
	{
		free(buf);
		buf = NULL;
	}
	return (1);
}
/*
int check_specials(char **buf)
{
	int		i;

	i = -1;
	while(buf[++i])
	{
		if (get_arg_type(buf[i]))
		{
			if (buf[i + 1] == NULL || get_arg_type(buf[i + 1]))
			{
				ft_printf("syntax error near unexpected token '%s'\n", buf[i]);
				return (1);
			}
		}
	}
	return (0);
}
*/
