/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 20:38:09 by gongarci          #+#    #+#             */
/*   Updated: 2025/01/16 22:20:37 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*find_path(t_minishell *shell, char *cmd)
{
	char	**paths;
	char	*goodpath;
	//char	*command;
	int		i;

	i = 0;
	//command = ft_strdup(cmd);
	if ((cmd[0] == '/' && access(cmd, 0) == 0))
		return (cmd);
	while (shell->env[i] && ft_strncmp(shell->env[i], "PATH=", 5))
		i++;
	paths = ft_split(shell->env[i] + 5, ':');
	cmd = ft_strjoin("/", cmd);
	i = -1;
	while (paths[++i])
	{
		goodpath = ft_gnlstrjoin(paths[i], cmd, ft_strlen(cmd));
		if (access(goodpath, 0) == 0)
			return (goodpath);
		free(goodpath);
	}
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("Command not found\n", 2);
	return (NULL);
}

	
//(ft_error(": command not found\n", 127, data, vals), NULL);
/*  gongarci@c3r6s2:~/Documents/Cursus/Projects/minishell/minishell$ << a < Makefile cat >a | << b ls
> asd
> a
> asd
> b
a  b  c  include  libft  Makefile  minishell  README.md  src
gongarci@c3r6s2:~/Documents/Cursus/Projects/minishell/minishell$ << a < Makefile ls | << b ls
asd
a
asd
b
a  b  c  include  libft  Makefile  minishell  README.md  src
gongarci@c3r6s2:~/Documents/Cursus/Projects/minishell/minishell$ << a < Makefile ls | << b ls
   
> asd
> asd
> a
> lk
> b
a  b  c  include  libft  Makefile  minishell  README.md  src
gongarci@c3r6s2:~/Documents/Cursus/Projects/minishell/minishell$ 
*/

void	ft_env(t_minishell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strchr(shell->env[i], '='))
			ft_printf("%s\n", shell->env[i]);
		i++;
	}
}
