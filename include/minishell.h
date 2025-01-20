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
	char	*cwd;
	char	*str;

}	t_prompt;

typedef struct s_minishell
{
	char		*command;
	char		**args;
	char		**env;
	char		**path;
	char		*pwd;
	char		*cwd;
	int			cwd_int;
	t_prompt	*prompt;
	t_exec		*exec;
	//t_path		*path;

}	t_minishell;


/*parsing functions*/
void	parsing(t_minishell *shell);
void		check_quotes(char **buf, int simple_quote, int double_quote);
int		check_other_quote(char **buf, int *i, char c);
/*built-ins functions*/
int		cd(t_minishell *shell, char **str);
int		pwd(void);
void	ft_env(t_minishell *shell);
void	ft_export(t_minishell *shell);
/* built-ins tools */
int	just_export(char *str);
void	free_arrays(char **array1, char **array2);
/* utils */
char	**strarray_copy(char **array);
char	**add_str_to_array(char **array, char *str);
char	**ft_arrjoin(char **arr1, char **arr2);
char	*find_path(t_minishell *shell, char *cmd);
/* builtins utils */
void	free_arrays(char **array1, char **array2);

#endif