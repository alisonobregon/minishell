/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 22:05:14 by gongarci          #+#    #+#             */
/*   Updated: 2025/01/09 22:06:22 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


/* Aqui vamos a crear el while loop principal
	*/

/*Aqui le doy los colorinchis y ademas si escuentra la ruta osea
el pwd imprime eso si no pues imprime la palabra minishell*/
void memory_allocated(t_minishell *shell)
{
	shell->args = ft_calloc(1, sizeof(char *)); //revisar si ultilizamos args
	shell->env = NULL;
	shell->path = NULL;
	shell->pwd = NULL;
	shell->cwd = NULL;
	shell->cwd_int = 0;
	shell->prompt = ft_calloc(1, sizeof(t_prompt));
	if (!shell->prompt)
		return ;
	shell->exec = NULL;
}

char	*get_prompt(t_minishell *shell)
{
	char	*pwd;
	char	*temp1;
	char	*temp2;
	char	*temp3;

	(void)shell;
	pwd = getenv("PWD");
	if (pwd)
	{
		temp1 = ft_strjoin(CYAN, pwd);
		temp2 = ft_strjoin(YELLOW, "->thelatambash$ ");
		temp3 = ft_strjoin(temp1, temp2);

		free(temp1);
		free(temp2);
		pwd = ft_strjoin(temp3, DEFAULT);
		free(temp3);
	}
	else
		pwd = ft_strjoin(CYAN "minishell$", YELLOW "->thelatambash$ " DEFAULT);	
	return(pwd);
}
int free_shell(t_minishell *shell)
{
	free(shell->prompt->cwd);
	free(shell->prompt->str);
	free(shell->prompt);
	free(shell->args);
	free(shell->path);
	free(shell->exec);
	free(shell);
	return (0);
}

char	*get_input(t_minishell *shell)
{
	char	*prompt;
	char	*buf;

	//shell->pwd = get_prompt(shell);
	prompt = get_prompt(shell);
	buf = readline(prompt);
	free(prompt);
	if (!buf) //no ha ingresado nada
		ft_printf("\n");
	if (ft_strlen(buf) == 0)
	{
		free(buf);
		return (NULL);
	}
	return(buf);
}
int command_list_clear(t_exec *command_list)
{
	t_exec	*temp;

	while (command_list)
	{
		temp = command_list->next;
		free(command_list->cmd);
		free(command_list->args);
		free(command_list->infile);
		free(command_list->outfile);
		free(command_list);
		
		command_list = temp;
	}
	return (0);
}
int add_history_to_file(char *str)
{
	int fd;

	fd = open(".history", O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (fd == -1)
	{
		perror("open");
		return (1);
	}
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
	close(fd);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_minishell	*shell;

	shell = ft_calloc(1, sizeof(t_minishell));
	if (!shell)
		return (1);
	shell->env = strarray_copy(env);
	memory_allocated(shell);

	while (1)
	{
		/*if (shell->cwd_int == 0) //preguntar
			shell->cwd = get_prompt(shell);
		shell->prompt->str = readline(shell->cwd);*/
		shell->prompt->str = get_input(shell);
		add_history(shell->prompt->str);
		add_history_to_file(shell->prompt->str);
		parsing(shell);
		print_command_list(shell->exec);
		//exec(shell);
		printf("prompt: %s\n", shell->prompt->str);
	}
	free_shell(shell);
	return (0);
}
