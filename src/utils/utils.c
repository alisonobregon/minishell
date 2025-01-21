/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:13:07 by marvin            #+#    #+#             */
/*   Updated: 2025/01/10 18:13:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*char	*find_path(t_minishell *shell)
{
	//char	**paths;
	//char	*goodpath;
	//char	*command;
	int		i;

	i = 0;
	command = ft_strdup(cmd);
	if ((cmd[0] == '/' && access(cmd, 0) == 0))
		return (cmd); 
	while (shell->env[i] && ft_strncmp(shell->env[i], "PATH=", 5))
		i++;
	//shell->path = ft_split(shell->env[i] + 5, ':');
	shell->path = shell->env[i];
	printf("paths: %s\n", shell->path);
	return (NULL);
 	cmd = ft_strjoin("/", cmd);
	i = -1;
	while (paths[++i])
	{
		goodpath = ft_gnlstrjoin(paths[i], cmd, ft_strlen(cmd));
		if (access(goodpath, 0) == 0)
			return (goodpath);
		free(goodpath);
	}
	ft_putstr_fd(command, 2);
	return (ft_error(": command not found\n", 127, data, vals), NULL); 
}*/

/* void	check_prompt(t_minishell *shell)
{
	int i;

	i = 0;
	shell->prompt->prompt = ft_split(shell->prompt->line, ' ');
	while(shell->prompt->prompt[i] != NULL)
	{
		if (ft_strmcmp(shell->prompt->prompt[i]), "<<", 2 == 0)
		{
			//heredoc++;
		}
		else if (ft_strmcmp)
	}
} */

char	*ft_array_to_str(char **array)
{
	char	*str;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (array[i] != NULL)
	{
		len += ft_strlen(array[i]);
		i++;
	}
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (array[i] != NULL)
	{
		ft_strlcat(str, array[i], len + 1);
		i++;
	}
	return (str);
}

char	**ft_arrjoin(char **arr1, char **arr2)
{
	char	**new_arr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_arr = ft_calloc(ft_len(arr1) + ft_len(arr2) + 1, sizeof(char *));
	if (!new_arr)
		return (NULL);
	while (arr1[i] != NULL)
	{
		new_arr[i] = ft_strdup(arr1[i]);
		i++;
	}
	while (arr2[j] != NULL)
	{
		new_arr[i] = ft_strdup(arr2[j]);
		i++;
		j++;
	}
	new_arr[i] = NULL;
	free_arrays(arr1, arr2);
	arr1 = NULL;
	arr2 = NULL;
	return (new_arr);
}

char	**add_str_to_array(char **array, char *str)
{
	char	**new_array;
	int		i;

	i = 0;
	if (!array)
	{
		new_array = ft_calloc(2, sizeof(char *));
		new_array[0] = ft_strdup(str);
		new_array[1] = NULL;
		return (new_array);
	}
	new_array = ft_calloc(ft_len(array) + 2, sizeof(char *));
	if (!new_array)
		return (NULL);
	while (array[i] != NULL)
	{
		new_array[i] = ft_strdup(array[i]);
		i++;
	}
	new_array[i] = ft_strdup(str);
	new_array[i + 1] = NULL;
	free_arrays(array, NULL);
	return (new_array);
}

char	**strarray_copy(char **array)
{
	char	**copy;
	int		i;

	i = 0;
	if (!array || !*array)
		return (NULL);
	copy = ft_calloc(ft_len(array) + 1, sizeof(char *));
	if (!copy)
		return (NULL);
	while (array[i] != NULL)
	{
		copy[i] = ft_strdup(array[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
