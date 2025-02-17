#include "../../include/minishell.h"

int ft_strarr_len(char ***array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i])
			i++;
	}
	return (i);
}/*
int strarr_append(char ***array, char *str)
{
	char	**new;
	int		i;

	i = -1;
	new = ft_calloc(sizeof(char *), ft_strarr_len(array) + 2);
	if (!new)
		return (1);
	while ((*array)[++i])
	{
		new[i] = ft_strdup((*array)[i]);
		if (!new[i])
			return (1);
	}
	new[i] = ft_strdup(str);
	if (!new[i])
		return (1);
	free(*array);
	*array = new;
	return (0);	
	
	
}*/
t_exec	*exec_lstlast(t_exec *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/*int append_in_args(char ***args, char *op, char ***array, int i)
{
	if (!(*args))
		return (1);
	if(ft_strncmp(*args[i], op, ft_strlen(op)) == 0)
	{
		if (strarr_append(array, *args[*i]))
			return (1);
		
	}
	
		
	return (1);
  }*/
char **str_array_append(char **array, char *str)
{
	char	**new;
	int		i;

	i = -1;
	new = ft_calloc(sizeof(char *), ft_strarr_len(&array) + 2);
	if (!new)
		return (NULL);
	while (array[++i])
	{
		new[i] = ft_strdup(array[i]);
		if (!new[i])
			return (NULL);
	}
	new[i] = ft_strdup(str);
	if (!new[i])
		return (NULL);
	free(array);
	return (new);
}
int command_lstappend(t_exec *new, char **buf)
{

	while (*buf && get_arg_type(*buf) == 0)
	{
		new->args = str_array_append(((new)->args), *buf);
		(*buf)++;
	}
	/*
	new->args = str_array_append(new->args, *buf);
	if (!(append_in_args(*buf, ">", &(new->outfile))))
		return (1);
	if (append_in_args(*buf, "<", &(new->infile)))
		return (1);
	if (append_in_args(*buf, ">>", &(new->outfile)))
		return (1);
	if (append_in_args(*buf, "<<", &(new->infile)))
		return (1);
	*/

	return (1);
}
int create_command_lst(t_minishell *shell)
{
	t_exec	*new;
	char	**buf;
	
	shell->exec = NULL;
	buf = shell->args;
	while (*buf && get_arg_type(*buf) == 0)
	{
		new = exec_new();
		if (!new)
			return (1);
		if (shell->exec != NULL)
		{
			new->next = exec_lstlast(shell->exec);
			printf("entra aqui al if con %s\n", *buf);
		}
		else
		{
			shell->exec = new;
			printf("entra aqui al else con %s\n", *buf);
		}
		new->cmd = ft_strdup(*buf);
		if(new->cmd == NULL)
			return (1);
		if (!(command_lstappend(new, buf)))
			return (1);
		if (buf)
			new->todo_next = get_arg_type(*buf);
		printf("buf: %s\n", *buf);
		buf++;
	}
	print_command_list(shell->exec);
	return (0);
}
int print_command_list(t_exec *command_list)
{
	t_exec	*temp;

	temp = command_list;
	while(temp)
	{
		printf("cmd: %s\n", temp->cmd);
		for (int i = 0; temp->args[i]; i++)
			printf("args[%d]: %s\n", i, temp->args[i]);
		printf("infile: %s\n", temp->infile);
		printf("outfile: %s\n", temp->outfile);
		printf("todo_next: %d\n", temp->todo_next);
		temp = temp->next;
	}
	return (0);
}