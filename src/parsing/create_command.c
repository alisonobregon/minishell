#include "../../include/minishell.h"

int ft_strarr_len(char **array)
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

int append_in_args(char ***buf, char *op, char ***array)
{
	if (!(**buf))
		return (1);
	if (ft_strlen(op) == ft_strlen(**buf) 
		&& !(ft_strncmp(**buf, op, ft_strlen(op))))
	{
		(*buf)++;
		if (!(str_array_append(array, **buf)))
			return (0);
		(*buf)++;
	}
	return (1);
}
int append_in_her_args(char ***buf, char *op, char ***array, t_exec *new)
{
	
	if (!(**buf))
		return (1);
	if (ft_strlen(op) == ft_strlen(**buf) 
		&& !(ft_strncmp(**buf, op, ft_strlen(op))))
	{
		(*buf)++;
		if (!(str_array_append(array, **buf)))
		{
			//printf("got here \n");
			return (0);
		}
		here_doc(&new, **buf);
		(*buf)++;
	}
	return (1);
}

int	str_array_append(char ***array, char *str)
{
	char	**new;
	int		i;

	i = 0;
	new = ft_calloc(sizeof(char *), ft_strarr_len(*array) + 2);
	if (!new)
	{
		printf("no se pudo asignar memoria\n");
		return (0);
	}
	if ((*array))
	{
		while ((*array)[i])
		{
			new[i] = ft_strdup((*array)[i]);
			//printf("new[%d] 48: %s\n", i, new[i]);
			if (!new[i])
				return (0);
			i++;
		}
	}
	new[i] = ft_strdup(str);
	//printf("new[%d]: %s\n", i, new[i]);
	if (!new[i])
		return (0);
	if (*array)
		free_array(*array);
	new[i + 1] = NULL;
	*array = new;
	//printf("array[%d] 2: %s\n", i, (*array)[i]);
	return (1);
}

void free_array(char **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
int command_lstappend(t_exec *new, char ***buf)
{
	while (**buf != NULL && *buf && (get_arg_type(**buf) == 0 || get_arg_type(**buf) == 1))
	{
		//printf("buf 3: %s\n", **buf);
		if (!(append_out_args(buf, ">", &(new->outfile))))
			return (0);
		else if (!(append_in_args(buf, "<", &(new->infile))))
			return (0);
		else if (!(append_out_args(buf, ">>", &(new->outfile))))
			return (0);
		else if (!(append_in_her_args(buf, "<<", &(new->heredoc), new)))
			return (0);
		if ((**buf) && (!get_arg_type(**buf)))
		{
			if (!(str_array_append(&(new->args), **buf)))
				return (0);
			(*buf)++;
		}
		//printf("buf 4: %s\n", **buf);
	}

	return (1);
}
int create_command_lst(t_minishell *shell)
{
	t_exec	*new;
	char	**buf;

	shell->exec = NULL;
	buf = shell->args;
	while (*buf != NULL && (get_arg_type(*buf) == 0 || get_arg_type(*buf) == 1))
	{
		printf("buf 0: %s\n", *buf);
		new = exec_new();
		if (!new)
			return (1);
		if (shell->exec != NULL)
		{
			exec_lstlast(shell->exec)->next = new;
			//new->next = exec_lstlast(shell->exec);
			//printf("entra aqui al if con %s\n", *buf);
		}
		else
		{
			shell->exec = new;
			//printf("entra aqui al else con %s\n", *buf);
		}
		
		new->cmd = ft_strdup(*buf);
		if(new->cmd == NULL)
			return (1);
		if (!(command_lstappend(new, &buf)))
			return (1);
		//printf("buf 1: %s\n", *buf);
		if (*buf != NULL)
			new->todo_next = get_arg_type(*buf);
		if (get_arg_type(new->cmd) == 1 && new->args)
			new->cmd = ft_strdup(new->args[0]);
		//printf("buf 1: %s\n", *buf);
		if (*buf && **buf)
    		buf++;
		//printf("buf 2: %s\n", *buf);
	}
	
	//printf("entra aqui al final\n");
	
	return (0);
}
int print_command_list(t_exec *command_list)
{
	t_exec	*temp;
	t_output	*temp_out;
	int i = 1;

	temp = command_list;
	while(temp)
	{
		printf("comando %d\n", i);
		printf("cmd: %s\n", temp->cmd);
		temp_out = temp->outfile;
		if (temp->args)
			for (int i = 0; temp->args[i]; i++)
				printf("args[%d]: %s\n", i, temp->args[i]);
		if (temp->infile)
		{
			for (int i = 0; temp->infile[i]; i++)
				printf("infile[%d]: %s\n", i, temp->infile[i]);
		}
		while (temp_out)
		{	
			printf("outfile: %s\n", temp_out->file);
			printf("action: %d\n", temp_out->action);
			temp_out = temp_out->next;
		}
		if (temp->heredoc)
		{
			for (int i = 0; temp->heredoc[i]; i++)
				printf("heredoc[%d]: %s\n", i, temp->heredoc[i]);
		}
		printf("todo_next: %d\n\n", temp->todo_next);
		temp = temp->next;
		i++;
	}
	return (0);
}
