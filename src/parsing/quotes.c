#include "../../include/minishell.h"

int set_quotes(char c, int *quotes)
{
	int c_quotes;

	c_quotes = *quotes;
	if (c == '\'')
	{
		if (c_quotes == 0)
			*quotes = 1;
		else if (c_quotes == 1)
			*quotes = 0;
	}
	if (c == '\"')
	{
		if (c_quotes == 0)
			*quotes = 2;
		else if (c_quotes == 2)
			*quotes = 0;
	}
	return (c_quotes);
}
int get_future_arglen(char *arg, char **env, int lex)
{
	int i;
	int quotes;
	int len;
	char *var_val;

	i = -1:
	len = 0;
	quotes = 0;
	while (arg[++i])
	{
		if (set_quotes(arg[i], &quotes) == quotes)
			len++;
		if (quotes != 1 && arg[i] == '$')
		{
			var_val = get_env()
		}
			
	}
}
char *malloc_new_arg(char *arg, char **env, int lex)
{
	char *new_arg;
	int future_len;

	future_len = 
}
int replace_env(char *arg, char **env, int last_exit)
{
	int i;
	int j;
	char *new_arg;
	char *temp;

	i = -1;
	j = 0;


int replace_quotes(char ***args, char **env, int last_exit)
{
	char **new_args;
	int i;

	i = 0;
	new_args = ft_calloc(ft_len(*args) + 1, sizeof(char *));
	if (!new_args)
		return (0);
	while ((*args)[i])
	{
		new_args[i] = replace_env((*args)[i], env, last_exit); //aqui hacerle comprobacion de errores
		i++;
	}
	new_args[i] = NULL;
	free_array(*args);
	*args = new_args;
	return (1);
}