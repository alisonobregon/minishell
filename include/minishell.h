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
#include <readline/readline.h>
#include <readline/history.h>


#define CYAN "\033[36m"
#define DEFAULT "\033[0m"

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
	char	**command;
	char	**env;
	int		infile;
	int		outfile;
	char	*limiter;
	int		pipe[2];
}	t_exec;

typedef struct s_prompt
{
	char	**prompt;
	char	*line;
}	t_prompt;

typedef struct s_minishell
{
	char		*command;
	char		**args;
	char		**env;
	char		**path;
	char		*pwd;
	t_prompt	*prompt;
	t_exec		*exec;
	//t_path		*path;

}	t_minishell;


// char	*find_path(t_minishell *shell);

/*built-ins functions*/
int		cd(t_minishell *shell);
#endif