/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliobreg <aliobreg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 18:19:13 by marvin            #+#    #+#             */
/*   Updated: 2025/04/05 21:21:58 by aliobreg         ###   ########.fr       */
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
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		temp1 = ft_str2join(CYAN, ft_strjoin(getenv("USER"), "@"), 0, 1);
		temp2 = ft_str2join(temp1, cwd, 1, 1);
		temp1 = ft_strjoin(YELLOW, "->thelatambash$ ");
		temp3 = ft_str2join(temp2, temp1, 1, 1);
		cwd = ft_str2join(temp3, DEFAULT, 1, 0);
	}
	else
		cwd = ft_strdup(CYAN "\nminishell$" DEFAULT);
	return(cwd);
}
