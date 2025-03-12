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
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>

# define CYAN "\033[36m"
# define YELLOW "\033[33m"
# define DEFAULT "\033[0m"
# define READ 0
# define WRITE 1

typedef struct s_output
{
	int				action; // 0 = write, 1 = append
	char			*file;
	struct	s_output *next;
}					t_output;

typedef struct s_heredoc
{
	char	*delimiter;
	int		here_d;
}			t_heredoc;

typedef struct s_exec
{
	char		*cmd;
	char		**args;
	char		**infile;
	t_output	*outfile;
	char		**heredoc;
	int			todo_next; // 0 = nothing,  2 = pipe
	int			i;
	int			fd_in;
	int			fd_out;
	struct s_exec *next;
}	t_exec;

typedef struct s_prompt
{
	char	*cwd;
	char	*str;

}	t_prompt;

typedef struct s_minishell
{
	pid_t		pid;
	char		**args;
	char		**env;
	char		**path;
	char		*pwd;
	char		*cwd;
	int			cwd_int;
	t_prompt	*prompt;
	t_exec		*exec;

}	t_minishell;


/*parsing functions*/
void	parsing(t_minishell *shell);
void	check_quotes(char **buf, int simple_quote, int double_quote);
int		check_other_quote(char **buf, int *i, char c);
int		split_args(t_minishell *shell, char *str);
int		get_end_index(char *str, int end);
int		get_quotes_end(char *str, int end);
int		get_arg_end(char *str, int end_index);
int		index_of_newline(char *str);
int		index_of(char *str, char *search, int n);
int 	get_arg_type(char *str);
int		ft_strarr_len(char **array);
int		create_command_lst(t_minishell *shell);
int		command_lstappend(t_exec *new, char ***buf);
int		append_in_args(char ***buf, char *op, char ***array);
int		str_array_append(char ***array, char *str);
t_exec	*exec_lstlast(t_exec *lst);
int		print_command_list(t_exec *command_list);
int		command_list_clear(t_exec *command_list);
t_exec	*exec_new(void);
void	free_array(char **array);
# define OUT_WRITE		0
# define OUT_APPEND		1
int		append_out_args(char ***buf, char *op, t_output **out);
int		outlst_append(t_output **out, char *filename, char *op);
t_output	*out_lstlast(t_output *out);
t_output	*outlst_new(char *filename, int action);
int			add_history_to_file(char *str);
int			check_specials(char **args);
void		ft_pipes(char **buf);
int			append_in_her_args(char ***buf, char *op, char ***array, t_exec *new);

/* Execution */
void	exec(t_minishell *shell);
char	*find_path(t_minishell *shell, char *cmd);
int		len_pipes(t_exec *exec);
int		fd_checker(t_exec **exec);
void	multi_dup(int read, int write);
void	exec_cmd(t_minishell *shell, t_exec *exec);

/*HERE DOC*/
void	here_doc(t_exec **exec, char *limiter);
void	unlinker(char **heredoc);

/*built-ins functions*/
int		ft_echo(char **args);
void	echo_args(char *str);
int		cd(t_minishell *shell, char **str);
int		cd(t_minishell *shell, char *str);
int		pwd(void);
void	ft_env(t_minishell *shell);
void	ft_export(t_minishell *shell);
/* built-ins tools */
int		just_export(char *str);
void	free_arrays(char **array1, char **array2);
int		is_builtin(t_exec *exec);

/* utils */
char	**strarray_copy(char **array);
char	*ft_array_to_str(char **array);
char	**add_str_to_array(char **array, char *str);
char	**ft_arrjoin(char **arr1, char **arr2);
/* builtins utils */
void	free_arrays(char **array1, char **array2);
#endif