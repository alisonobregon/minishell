#include "../../include/minishell.h"

int strarr_len(char ***array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i])
			i++;
	}
	return (i);
}
int strarr_append(char ***array, char *str)
{
	char	**new;
	int		i;

	i = -1;
	new = ft_calloc(sizeof(char *), ft_strlen(array) + 2);
	if (!new)
		return (1);
	while ((*array)[++i])
		new[i] = ft_strdup((*array)[i]);
	
	
}
t_exec	*exec_lstlast(t_exec *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int append_in_args(char **args, char *op, char ***array)
{
	if (!(*args))
		return (1);
	if(ft_strncmp(*args, op, ft_strlen(op)) == 0)
	{
		*i++;
	}
	
		
	return (0);
}
int command_lstappend(t_exec **new, char **args, int *i)
{
	while(cmd[++*i])
	{
		if (!append_in_args())
	}
}
int create_command_lst(t_exec **command_list, char **buf)
{
	t_exec	*new;
	int		i;

	i = -1;
	command_list = NULL;
	while (buf[++i])
	{
		new = ft_calloc(1, sizeof(t_exec));
		if (!new)
			return (1);
		if (*command_list)
			exec_lstlast(*command_list)->next = new;
		else
			*command_list = new;
		new->cmd = ft_strdup(buf[i]);
		if(new->cmd == NULL)
			return (1);
		

	}

}