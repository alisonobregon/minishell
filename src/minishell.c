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
char	*get_prompt(t_minishell *shell)
{
	char	*pwd;
	char	*tmp;

	(void)shell;
	pwd = getenv("PWD");  //Aqui creo que hay que hacer una funcion porque retorna int y quiero el char
	if(pwd)
	{
		tmp = ft_strjoin("\n"CYAN, pwd);
		pwd = ft_strjoin(tmp, DEFAULT); 
		free(tmp);
	}
	else
		pwd = ft_strdup(CYAN "\nminishell" DEFAULT);
	//AQUI PONDRIAMOS YA SI EL COMANDO FUE EXITOSO O NO
	return(pwd);
}
//readline muestra el texto y espera a que el usuario ingrese una linea
//aqui ya tenemos buff que es lo que recibe;
char	*get_input(t_minishell *shell)
{
	char	*prompt;
	char	*buf;

	prompt = get_prompt(shell);
	buf = readline(prompt);
	free(prompt);
	if (!buf) //no ha ingresado nada
	{
		ft_printf("\n");
	}
	return(buf);
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	*shell;
	char	*str;

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
	shell->path = ft_split(getenv("PATH"), ':');
	if (!shell->path)
		shell->path[0] = ft_strdup("./") ;
	while(1)
	{
		str = get_input(shell);
		if (!str)
			continue;
		//shell->prompt->line = get_next_line(0);
		
		if (!shell->prompt->line)
			break ;
		printf("prompt: %s\n", shell->prompt->line);
		// Read command
		// Parse command
		// Execute command
		// Print output
	}
	return (0);
}
