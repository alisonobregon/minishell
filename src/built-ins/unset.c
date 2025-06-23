/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:34:33 by gongarci          #+#    #+#             */
/*   Updated: 2025/04/05 22:19:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	index_array(char **array, char *str)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (!ft_strncmp(array[i], str, ft_strlen(array[i])))
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_ptr_in_array(char **array, char *str)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (!ft_strncmp(array[i], str, ft_strlen(array[i])))
			return (array[i]);
		i++;
	}
	return (NULL);
}

int	str_in_array(char **array, char *str)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		if (!ft_strncmp(str, array[i], ft_strlen(str)))
			return (1);
		i++;
	}
	return (0);
}

int	ft_chrlen(char *str, char c)
{
	int		i;
	int		counter;

	i = 0;
	counter = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			counter++;
		i++;
	}
	return (counter);
}

void	ft_unset(t_minishell *shell, char **args)
{
	int	i;

	i = 0;
	if (!args[0] || !args[1])
		return ;
	while (args[i])
	{
		if (str_in_array(shell->env, args[i]))
		{
			shell->env = rm_env_var(shell, args[i]);
		}
		i++;
	}
}
