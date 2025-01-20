#include "../../include/minishell.h"

int ft_countpipes(char *str)
{
	int i;
	int res;
	char quote;

	i = -1;
	res = 0;
	while (str[++i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			quote = str[i];
			i++;
			while(str[i] && str[i] != quote)
				i++;
		}
		if ((str[i] == '|' && (str[i + 1] == '|' || str[i + 1] == '\0' || ft_blank(str[i + 1]) != 1)) || str[0] == '|')
			ft_printf("syntax error near unexpected token '|'");
		if (s[i] == '|')
			res++;
	}
	return(res);
}

char **split_pipes(char *str)
{
	char	**res;
	int		i;

	i = -1;
	res = ft_calloc(sizeof(char *), ft_countpipes(str) + 2);
	if(!res)
		exit(1); //aqui poner o hacer una funcion de mensaje de error
	eres 

}