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
	shell->args = ft_calloc(1, sizeof(char *));
	if (!shell->prompt)
		return ;
}

char	*get_prompt(t_minishell *shell)
{
	char	*pwd;
	char	*temp1;
	char	*temp2;

	(void)shell;
	pwd = getenv("PWD"); //hacer una funcion porque retorna int y quiero el char
	//user = getenv("USER");
	if(pwd)
	{
		temp1 = ft_strjoin(CYAN, pwd);
		temp2 = ft_strjoin(temp1, "$ ");
		free(temp1);
		pwd = ft_strjoin(temp2, DEFAULT);
		free(temp2);
		//de esta manera nos ahorramos una variable y se puede imprimir el usuario tambien
		//free(tmp);
	}
	else
		pwd = ft_strdup(CYAN "\nminishell$" DEFAULT);
	//AQUI PONDRIAMOS YA SI EL COMANDO FUE EXITOSO O NO
	return(pwd);
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
		free(command_list);
		command_list = temp;
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	*shell;

	shell = ft_calloc(1, sizeof(t_minishell));
	if (!shell)
		return (1);
	(void)argc;
	(void)argv;
	shell->env = env;
	/* if (getenv("PATH") == NULL)
	{
		 buscar path find_path y asignar o de lo contrario
		return 
	} */
	memory_allocated(shell);
	shell->path = ft_split(getenv("PATH"), ':');
	if (!shell->path)
		shell->path[0] = ft_strdup("./") ;
	ft_printf("\033[1;1H\033[2J");
	while (1)
	{
		shell->cwd = get_prompt(shell);
		shell->prompt->str = readline(shell->cwd);
		parsing(shell);
		if (ft_strncmp(shell->prompt->str , "cd", 2) == 0)
		{
			cd(shell, &shell->prompt->str);
			continue;
		}
		printf("prompt: %s\n", shell->prompt->str);
		command_list_clear(shell->exec);
		// Read command
		// Parse command
		// Execute command
		// Print output
	}
	return (0);
}
