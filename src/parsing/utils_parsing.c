#include "../../include/minishell.h"

int	index_of(char *str, char *search, int n)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (ft_strncmp(str + i, search, ft_strlen(search)) == 0)
			n--;
		if (n <= 0)
			break ;
	}
	return (i); //verificar esta vaina
}