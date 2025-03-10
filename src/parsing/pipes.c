#include "../../include/minishell.h"

int ft_pipes(char **buf)
{
	int i;
	char *pipe;
	char *temp;

	i = -1;
	while (buf[++i])
	{
		if (get_arg_type(buf[i]) == 2)
		{
			if (i == 0)
				return (0);
			if (buf[i + 1] == NULL)
			{
				pipe = readline("pipe>");
				temp = ft_strjoin(buf[i], "\n");
				temp = ft_strjoin(temp, pipe);
				free(pipe);
				free(buf); //free array verifico que libere
				*buf = temp;
				return (ft_pipes(buf));
			}
		}
	}
	return (0);
}

