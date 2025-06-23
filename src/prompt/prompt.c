/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliobreg <aliobreg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 18:19:13 by marvin            #+#    #+#             */
/*   Updated: 2025/04/08 20:33:20 by aliobreg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_prompt(t_minishell *shell)
{
	char	*cwd;
	char	*temp1;
	char	*temp2;
	char	*temp3;
	char	*user;

	(void)shell;
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		user = get_env("$USER", shell->env, shell->status);
		temp1 = ft_str2join(CYAN, ft_strjoin(user, "@"), 0, 1);
		temp2 = ft_str2join(temp1, cwd, 1, 1);
		temp1 = ft_strjoin(YELLOW, "->thelatambash$ ");
		temp3 = ft_str2join(temp2, temp1, 1, 1);
		cwd = ft_str2join(temp3, DEFAULT, 1, 0);
		free(user);
	}
	else
		cwd = ft_strdup(CYAN "\nminishell$" DEFAULT);
	return (cwd);
}
