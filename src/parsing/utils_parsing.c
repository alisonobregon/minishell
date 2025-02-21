#include "../../include/minishell.h"


int get_arg_type(char *str)
{
	if (!ft_strncmp(str, ">>", 2) || !ft_strncmp(str, "<<", 2) 
		|| !ft_strncmp(str, "<", 1) || !ft_strncmp(str, ">", 1))
		return (1);
	if (!ft_strncmp(str, "|", 1))
		return (2); //devuelve 2 si es un pipe
	return (0);
}
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
		//printf("i de str: %s %d\n",str + i, i);
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

t_exec *exec_new(void)
{
	t_exec	*new;

	new = ft_calloc(1, sizeof(t_exec));
	if (!new)
		return (NULL);
	new->args = NULL;
	new->cmd = NULL;
	new->infile = NULL;
	new->outfile = NULL;
	new->todo_next = 0;
	new->next = NULL;
	return (new);
}