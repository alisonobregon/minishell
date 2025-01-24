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

typedef struct s_exec
{
	//char	*path; //no se si este lo utilizas
	char	*cmd; 
	int		infile;
	int		outfile;
	char	*limiter;
	int		pipe[2];
	struct s_exec *next;
	{
		/* data */
	};
	
}	t_exec;

typedef struct s_prompt
{
	char	*cwd;
	char	*str;

}	t_prompt;

typedef struct s_minishell
{
	char		**args;
	char		**env;
	char		**path;
	char		*pwd;
	char		*cwd;
	t_prompt	*prompt;
	t_exec		*exec;

}	t_minishell;


/*parsing functions*/
void	parsing(t_minishell *shell);
void	check_quotes(char **buf, int simple_quote, int double_quote);
int		check_other_quote(char **buf, int *i, char c);
void	parsing(t_minishell *shell);
int		split_args(t_minishell *shell, char *str);
int		get_end_index(char *str, int end);
int		get_quotes_end(char *str, int end);
int		get_arg_end(char *str, int end_index);
int		index_of_newline(char *str);
int		index_of(char *str, char *search, int n);

/*built-ins functions*/
int		cd(t_minishell *shell, char **str);

#endif