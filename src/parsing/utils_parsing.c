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

int index_of_newline(char *str)
{
	int index;
	int temp;

	index = index_of(str, " ", 1);
	temp = index_of(str, "\t", 1);
	if (temp || str[0] == '\t')
		if (temp < index)
			index = temp;
	return (index);
}