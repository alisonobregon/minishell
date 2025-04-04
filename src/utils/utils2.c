/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 20:35:54 by gongarci          #+#    #+#             */
/*   Updated: 2025/03/31 15:53:29 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**rm_str_from_array(char **array, char *str)
{
	char	**new_array;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_array = ft_calloc(ft_len(array), sizeof(char *));
	if (!new_array)
		return (NULL);
	while (array[i] != NULL)
	{
		if (ft_strncmp(array[i], str, ft_strlen(str)) != 0)
		{
			new_array[j] = ft_strdup(array[i]);
			j++;
		}
		i++;
	}
	new_array[j] = NULL;
	free_arrays(array, NULL);
	return (new_array);
}

int	contains_only(char *str, int c)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != c)
			return (0);
	}
	return (1);
}

void	print_array(char **array)
{
	int	i;

	i = 0;
	if (!array || *array == NULL)
		return ;
	while (array[i] != NULL)
	{
		ft_printf("%s\n", array[i]);
		i++;
	}
}
void	round_frees(t_minishell **shell)
{
	if ((*shell)->prompt)
	{
		free((*shell)->prompt->str);
		(*shell)->prompt->str = NULL;
		free((*shell)->prompt);
		(*shell)->prompt = NULL;
	}
	if ((*shell)->exec)
	{
		if ((*shell)->exec->cmd)
		{
			free((*shell)->exec->cmd);
			(*shell)->exec->cmd = NULL;
		}
		if ((*shell)->exec->args)
		{
			free_array((*shell)->exec->args);
			(*shell)->exec->args = NULL;
		}
		if ((*shell)->exec->infile && ft_len((*shell)->exec->infile) > 0)
		{
			free_array((*shell)->exec->infile);
			(*shell)->exec->infile = NULL;
		}
		if ((*shell)->exec->heredoc)
		{
			free_array((*shell)->exec->heredoc);
			(*shell)->exec->heredoc = NULL;
		}
		if ((*shell)->exec->outfile)
		{
			free_output(&(*shell)->exec->outfile);
			(*shell)->exec->outfile = NULL;
		}
		free((*shell)->exec);
		(*shell)->exec = NULL;
	}
 	if ((*shell)->args)
		free_array((*shell)->args);
	(*shell)->args = NULL;
}
int	check_prompt_str(t_minishell *shell)
{
	int	i;
	int	chars;
	int	check;
	
	i = 0;
	chars = 0;
	if (!shell || !shell->prompt || shell->prompt->str == NULL)
		return (0);
	while (shell->prompt->str[i])
	{
		if (!ft_blank(shell->prompt->str[i]))
		{
			chars++;
			if (chars == 1)
				check = shell->prompt->str[i];
		}
		i++;
	}
	if ((chars == 0 || chars == 1 ) && i > 1)
	{
		ft_printf("%c: command not found\n", check);
		return (0);
	}
	return (1);
}

void	print_all_shell(t_minishell *shell)
{
	if ((shell) == NULL)
		return ;
	ft_printf("--shell");
	if (shell->prompt)
		ft_printf("shell->prompt: \n");
	if (shell->env)
		ft_printf("shell->env: \n");
	if (shell->path)
		ft_printf("shell->path: \n");
	if (shell->exec)
		ft_printf("shell->exec: \n");
	if(shell->cwd)
		ft_printf("shell->cwd: \n");
	if (shell->args)
		ft_printf("shell->args: \n");
}

