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
	char	*user;

	(void)shell;
	pwd = getenv("PWD");  //hacer una funcion porque retorna int y quiero el char
	user = getenv("USER");
	if(pwd || user)
	{
		pwd = ft_strjoin((ft_strjoin(CYAN, user)), pwd);
		pwd = ft_strjoin((ft_strjoin(pwd, "$ ")), DEFAULT);
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

	//shell->pwd = readline(prompt);
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
		if (ft_strncmp(str, "cd", 3) == 0)
		{
			cd(shell);
			continue;
		}
		/* if (!str)
			continue; */
		printf("prompt: %s\n", str);
		// Read command
		// Parse command
		// Execute command
		// Print output
	}
	return (0);
}
