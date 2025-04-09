/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:15:18 by aliobreg          #+#    #+#             */
/*   Updated: 2025/04/09 21:21:08 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_arg_end(char *str, int end_index)
{
	char	**split;
	int		is_sp;
	int		is_sep;
	int		i;

	i = -1;
	split = ft_split("<< < >> > || | && &", ' ');
	if (!split)
		return (-1);
	is_sp = index_of_newline(str + end_index);
	while (split[++i])
	{
		is_sep = index_of(str + end_index, split[i], 1);
		if (is_sep < is_sp)
			return ((end_index + is_sep) + free_array(split));
	}
	return ((end_index + is_sp) + free_array(split));
}

int	get_quotes_end(char *str, int end)
{
	int	end_index;

	end_index = -2;
	if (str[0] == 39)
		end_index = get_arg_end(str, index_of(str + 1, "'", 1) + 2);
	else if (str[0] == 34)
		end_index = get_arg_end(str, index_of(str + 1, "\"", 1) + 2);
	else if (end > -1 && index_of(str, "'", 1) < end)
		end_index = get_arg_end(str + 1, index_of(str, "'", 2) + 2);
	else if (end > -1 && index_of(str, "\"", 1) < end)
		end_index = get_arg_end(str + 1, index_of(str, "\"", 2) + 2);
	return (end_index);
}

int	get_end_index(char *str, int end)
{
	char	**split;
	int		end_index;
	int		i;

	i = -1;
	split = ft_split("<< < >> > || | && &", ' ');
	if (!split)
		return (0);
	end_index = get_quotes_end(str, end);
	if (end_index == 0)
		return ((0) + free_array(split));
	if (end_index != -2)
		return ((end_index) + free_array(split));
	while (split[++i])
	{
		if ((end > -1 && index_of(str, split[i], 1) < end))
			return (index_of(str, split[i], 1) + free_array(split));
		if (index_of(str, split[i], 1) == 0)
			return (ft_strlen(split[i]) + free_array(split));
	}
	return (end + free_array(split));
}

int	split_args(t_minishell *shell, char *str)
{
	int	i;
	int	j;
	int	end_index;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '\t' || str[i] == ' ')
			continue ;
		if (str[i] == '>' || str[i] == '<' || str[i] == 34 || str[i] == 39
			|| str[i] == '|' || str[i] == '&')
			end_index = get_end_index(str + i, -1);
		else
			end_index = get_end_index(str + i, get_arg_end(str + i, 0));
		if (end_index < 0)
			return (-1 + free_array(shell->args));
		shell->args[j] = ft_strldup(str + i, end_index);
		i += ft_strlen(shell->args[j]) - 1;
		j++;
	}
	return (1);
}

void	parsing(t_minishell *shell)
{
	shell->args = (char **)ft_calloc(MAX_ARGUMENTS, sizeof(char *));
	if (!check_quotes(&(shell->prompt->str), 0, 0))
	{
		shell->status = 2;
		return ;
	}
	ft_pipes(&(shell->prompt->str));
	if (!split_args(shell, shell->prompt->str))
		return ;
	if (!check_specials(shell->args))
	{
		shell->status = 2;
		return ;
	}
	if (!create_command_lst(shell))
		return ;
	free_array(shell->args);
	shell->args = NULL;
}
