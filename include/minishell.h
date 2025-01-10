/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 22:03:05 by gongarci          #+#    #+#             */
/*   Updated: 2025/01/09 22:04:29 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

typedef struct s_path
{
	char	*path;
	char	**env;
	char	*SHLVL;
}			t_path;
typedef struct s_exec
{
	char	*path;
	char	**cmd;
	char	**env;
	int		infile;
	int		outfile;
	char	*limiter;
	
}	t_exec;

typedef struct s_minishell
{
	char	*command;
	char	**args;
	char	**env;
	char	*line;

}	t_minishell;

#endif