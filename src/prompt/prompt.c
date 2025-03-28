/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliobreg <aliobreg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 18:19:13 by marvin            #+#    #+#             */
/*   Updated: 2025/03/28 19:44:33 by aliobreg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


char	*get_prompt(t_minishell *shell)
{
	char	*cwd;
	char	*temp1;
	char	*temp2;
	char	*temp3;

	(void)shell;
	if (shell->cwd)
	{
		free(shell->cwd);
		shell->cwd = NULL;
	}
	cwd = getcwd(NULL, 0);
	//printf("pwd in get_prompt: %s\n", pwd);
	// if (cwd)
	// {
	// 	temp1 = ft_strjoin(CYAN, getenv("USER"));
	// 	temp2 = ft_str2join(temp1, cwd, 1 ,1);
	// 	temp1 = ft_strjoin(YELLOW, "->thelatambash$ ");
	// 	temp3 = ft_str2join(temp2, temp1, 1, 1);
	// 	cwd = ft_str2join(temp3, DEFAULT, 1, 0);
	// }
	// else
	// 	cwd = ft_strdup(CYAN "\nminishell$" DEFAULT);
	if (ft_len(shell->env) > 2)
	{
		temp1 = ft_strjoin(CYAN, getenv("USER"));
		temp2 = ft_str2join(temp1, cwd, 1 ,1);
		temp1 = ft_strjoin(YELLOW, "->thelatambash$ ");
		temp3 = ft_str2join(temp2, temp1, 1, 1);
		cwd = ft_str2join(temp3, DEFAULT, 1, 0);
	}
	else
		cwd = ft_strdup(CYAN "\nminishell$ " DEFAULT);
	//free(shell->cwd); hay que verlo
	return(cwd);
}
