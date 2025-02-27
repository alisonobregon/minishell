/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfiles.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:32:22 by aliobreg          #+#    #+#             */
/*   Updated: 2025/02/26 20:40:23 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_output	*outlst_new(char *filename, int action)
{
	t_output	*new;
	new = ft_calloc(sizeof(t_output), 1);
	if (!new)
		return (NULL); //recordatorio amable para mejor cambiar a 0 y por 1 guapa
	new->file = ft_strdup(filename);
	if(!new->file)
	{
		free(new);
		return(NULL);
	}
	new->action = action;
	new->next = NULL;
	return (new);
}
t_output	*out_lstlast(t_output *out)
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
	//printf("op: %s\n", op);
	if (ft_strlen(op) == 2) 
	{
		printf("op 2: %s\n", op);
		action = OUT_APPEND;
	}
	new = outlst_new(filename, action);
	if (!new)
		return (0);
	if (*out)
		out_lstlast(*out)->next = new;	
	else
		(*out) = new;
	return (1);

}
int append_out_args(char ***buf, char *op, t_output **out)
{
	if (!(**buf))
		return (0);
	if (ft_strlen(op) == ft_strlen(**buf) 
		&& !(ft_strncmp(**buf, op, ft_strlen(op))))
	{
		(*buf)++;
		if (*buf && !(outlst_append(out, **buf, op)))
			return (0);
		(*buf)++;
	}		
	return (1);
  }
