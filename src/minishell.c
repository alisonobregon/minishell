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
	shell->prompt = ft_calloc(1, sizeof(t_prompt));
	shell->args = ft_calloc(1, sizeof(char *)); //revisar si ultilizamos args
	shell->path = NULL;
	if (!shell->prompt)
		return ;
}

char	*get_prompt(t_minishell *shell)
{
	char	*pwd;
	char	*temp1;
	char	*temp2;
	char	*temp3;

	(void)shell;
	pwd = getenv("PWD"); //hacer una funcion porque retorna int y quiero el char
	//user = getenv("USER");
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
	{
		pwd = ft_strjoin(CYAN "minishell$", YELLOW "->thelatambash$ " DEFAULT);
		
	}//AQUI PONDRIAMOS YA SI EL COMANDO FUE EXITOSO O NO
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
	{
		ft_printf("\n");
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

	printf("str de add: %s\n", str);
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

//if (shell->env == NULL) no tenemos enviroment
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
	/* if (getenv("PATH") == NULL)
	{
		 buscar path find_path y asignar o de lo contrario
		return 
	} */
	/*shell->path = ft_split(getenv("PATH"), ':');
	if (!shell->path)
		shell->path[0] = ft_strdup("./") ;*/
	//ft_printf("\033[1;1H\033[2J");//revisar 
	while (1)
	{
		if (shell->cwd_int == 0) //preguntar
			shell->cwd = get_prompt(shell);
		shell->prompt->str = readline(shell->cwd);
		add_history(shell->prompt->str);
		add_history_to_file(shell->prompt->str);
		parsing(shell);
		printf("el error no esta en el parseo");
		//print_command_list(shell->exec);
		exec(shell);
		printf("prompt: %s\n", shell->prompt->str);
	}
	return (0);
}
