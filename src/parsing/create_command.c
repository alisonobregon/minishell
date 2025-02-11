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

/*char *append_in_args(char ***args, char *op, char ***array, int i)
{
	if (!(*args))
		return (1);
	if(ft_strncmp(*args[i], op, ft_strlen(op)) == 0)
	{
		if (strarr_append(array, *args[*i]))
			return (1);
		
	}
	
		
	return (0);
  }*/
/*char command_lstappend(t_exec *new, char ***buf)
{

	if (append_in_args(*buf, ">", &(new->outfile)))
		return (1);
	if (append_in_args(*buf, "<", &(new->infile)))
		return (1);
	if (append_in_args(*buf, ">>", &(new->outfile)))
		return (1);
	if (append_in_args(*buf, "<<", &(new->infile)))
		return (1);
	if (append_in_args(*buf, "|", &(new->pipe)))
		return (1);
	return (0);
}*/
int create_command_lst(t_minishell *shell)
{
	t_exec	*new;
	t_exec	**command_list;
	char	**buf;

	command_list = NULL;
	buf = shell->args;
	while (*buf && get_arg_type(*buf) == 0)
	{
		new = ft_calloc(1, sizeof(t_exec));
		if (!new)
			return (1);
		if (*command_list)
			exec_lstlast(*command_list)->next = new;
		else
			*command_list = new;
		new->cmd = ft_strdup(*buf);
		if(new->cmd == NULL)
			return (1);
		//if (!(command_lstappend(new, buf)))
			//return (1);
		if (buf)
			new->todo_next = get_arg_type(*buf);
		buf++;		
	}
	print_command_list(*command_list);
	return (0);
}
int print_command_list(t_exec *command_list)
{
	t_exec	*temp;

	temp = command_list;
	while (temp)
	{
		printf("cmd: %s\n", temp->cmd);
		printf("infile: %s\n", temp->infile);
		printf("outfile: %s\n", temp->outfile);
		printf("pipe: %s\n", temp->todo_next);
		temp = temp->next;
	}
	return (0);
}