#include "../../include/minishell.h"

void ft_pipes(char **buf)
{
	int i;
	char *pipe;
	char *temp;

	i = -1;
	while ((*buf)[++i])
	{
		if (get_arg_type(&((*buf)[i])) == 2)
		{
			if (i == 0)
				return ;
			else
				i++;
			while ((*buf)[i] >= 1 && (*buf)[i] <= 32)
				i++;
			if ((*buf)[i] == '\0')
			{
				while (1)
				{
					pipe = readline("pipe>");
					if (pipe && *pipe)
					{
						//if (get_arg_type(pipe) == 0)
						//{
							temp = ft_strjoin(*buf, pipe);
							free(pipe);
							free(*buf); //free array verifico que libere
							*buf = temp;
							break;
						//}
					}
					free(pipe);
				}
			}
		}
	}
}

