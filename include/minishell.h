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
# include <signal.h>
# include <errno.h>

# define CYAN "\033[36m"
# define YELLOW "\033[33m"
# define DEFAULT "\033[0m"
# define READ 0
# define WRITE 1
# define MAX_ARGUMENTS 256

extern sig_atomic_t	 g_sigint;

/*enum e_arg_type
{
	CMD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC
};
*/
typedef struct s_output
{
	int				action; // 0 = write, 1 = append
	char			*file;
	struct	s_output *next;
}					t_output;

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
	//int			type;
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
	int			status;
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
int		command_list_clear(t_exec **command_list);
t_exec	*exec_new(void);
int		free_array(char **array);
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
int			 free_shell(t_minishell *shell);
int			free_output(t_output **output);
int			check_specials(char **args);

/*Signals :)*/
void	wait_signal(int sig);

/*vars y env*/
int replace_quotes(char ***args, char **env, int last_exit);
int replace_var(char *arg, char *new_args, int *n_args);
char	*replace_env(char *arg, char **env, int last_exit);
char	*malloc_new_arg(char *arg, char **env, int lex);
int		get_future_arglen(char *arg, char **env, int lex);
int 	set_quotes(char c, int *quotes);
int		get_env_len(char *str);
char *get_env(char *env_name, char **env, int last_exit);
int env_name_len(char *env_name);

/*PROMPT*/
char	*get_prompt(t_minishell *shell);
int		add_history_to_file(char *str);
/* Execution */
void	exec(t_minishell *shell);
void	one_cmd(t_minishell *shell);
char	*find_path(t_minishell *shell, char *cmd);
int		len_pipes(t_exec *exec);
int		fd_checker(t_exec **exec);
void	multi_dup(int read, int write);
void	exec_cmd(t_minishell *shell, t_exec *exec);
void	free_exec_node(t_exec **exec);

/*HERE DOC*/
void	here_doc(t_exec **exec, char *limiter);
void	unlinker(char **heredoc);

/*built-ins functions*/
int		cd(t_minishell *shell, char **arr);
int		ft_echo(char **args);
void	echo_args(char *str);
int		pwd(void);
void	ft_env(t_minishell *shell);
void	ft_export(t_minishell *shell);
/* built-ins tools */
int		just_export(char *str);
void	free_arrays(char **array1, char **array2);
int		is_builtin(t_minishell *shell, char *cmd);

/* builtins utils */
void	free_arrays(char **array1, char **array2);

/* utils */
char	**strarray_copy(char **array);
char	*ft_array_to_str(char **array);
char	**add_str_to_array(char **array, char *str);
char	**ft_arrjoin(char **arr1, char **arr2);
char	*ft_str2join(char *s1, char *s2, int f1, int f2);
size_t	ft_strcat(char *dest, const char *src);
int		contains_only(char *str, int c);

#endif