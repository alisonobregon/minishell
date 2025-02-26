/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 20:38:09 by gongarci          #+#    #+#             */
/*   Updated: 2025/02/26 21:30:18 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

	
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
