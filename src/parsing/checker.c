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

int	check_other_quote(char **buf, int *i, char c)
{
	int	n;

	n = 1;
	while ((*buf)[*i + 1] && (*buf)[*i + 1] != c)
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
	int		i;
	char	*dquote;

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
			return (0);
		}
		*buf = new_buf_quotes(buf, dquote);
		return (check_quotes(buf, 0, 0));
	}
	wait_signal();
	return (2);
}

char	*new_buf_quotes(char **buf, char *dquote)
{
	char	*temp;
	char	*temp2;

	temp = ft_strjoin(*buf, "\n");
	temp2 = ft_strjoin(temp, dquote);
	free(temp);
	free(dquote);
	free(*buf);
	return (temp2);
}

int	check_specials(char **args)
{
	int	i;
	int	is_special;
	int	is_special2;

	i = -1;
	if (!args)
		return (0);
	while (args[++i] != NULL)
	{
		is_special = get_arg_type(args[i]);
		if (is_special)
		{
			if (args[i + 1] == NULL)
				return (print_and_return("minishell: syntax error near \
			unexpected token `newline'", NULL, 0));
			is_special2 = get_arg_type(args[i + 1]);
			if ((is_special == 2 || is_special == 3 || is_special == 4) \
			&& is_special2)
				return (print_and_return("minishell: syntax error near \
			unexpected token :", args[i + 1], 0));
			if (is_special == 1 && is_special2 == 1)
				return (print_and_return("minishell: syntax error near \
			unexpected token :", args[i + 1], 0));
		}
	}
	return (1);
}

int	print_and_return(char *src, char *args, int i)
{
	if (args)
	{
		printf("%s %s\n", src, args);
		return (i);
	}
	else
	{
		printf("%s\n", src);
		return (i);
	}
	return (1);
}
