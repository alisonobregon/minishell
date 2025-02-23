#include "../../include/minishell.h"

t_output	*outlst_new(char *filename, int action)
{
	t_output	*new;
	new = ft_calloc(sizeof(t_output), 1);
	if (!new)
		return (1); //recordatorio amable para mejor cambiar a 0 y por 1 guapa
	new->file = ft_strdup(filename);
	if(!new->filename)
	{
		free(new);
		return(1);
	}
	new->action = action;
	new->next = NULL;
	return (new);
}
t_output	*out_lstlast(t_exec *out)
{
	if (!out)
		return (NULL);
	while (out->next)
		out = out->next;
	return (out);
}
int	outlst_append(t_output **out, char *filename, char *op)
{
	t_output	*new;
	int			action;

	action = OUT_WRITE; // para >
	if (ft_strlen(op) == 2)
		action = OUT_APPEND;
	new = outlst_new(filename, action);
	if (!new)
		return (1);
	if (*out)
		out_lstlast(*out)->next = new;	
	else
		(*out) = new;
	return (0);

}
int append_out_args(char ***buf, char *op, t_output **out)
{
	if (!(**buf))
		return (1);
	if(!(ft_strncmp(**buf, op, ft_strlen(op))))
	{
		(*buf)++;
		if (*buff && !(outlst_append(out, **buf, op)))
			return (0);
		(*buf)++;
	}		
	return (1);
  }