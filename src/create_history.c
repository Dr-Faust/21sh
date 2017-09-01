#include "minishel.h"

/*static t_hist	create_history(char *line, int id)
{
	t_hist	*list;
	
	if(!(list = (t_hist *)ft_malloc(sizeof(t_hist))))
		error_exit(sh, mem_alloc_err);
	list->id = id;
	list->line = ft_strdup(line);
	list->bytes_str = ft_strdup(g_info->bytes_quote_str);
	list->prev = 0;
	list->next = 0;
	return (list);
}

static void		push_back_history(t_hist **head, t_hist *new)
{
	if (!*head)
	{
		*head = new;
		(*head)->prev = new;
		(*head)->prev->next = (*head);
		(*head)->next = create_history(0, 0);
		(*head)->next->prev = (*head);
		(*head) = (*head)->next;
		(*head)->= new;
		return ;
	}
	while ((*head)->next)
		(*head) = (*head)->next;
	new->prev = (*head)->prev;
	(*head)->prev->next = new;
	new->next = (*head);
	(*head)->prev = new;
}

void			add_to_history(char *line, t_hist **hist, int id)
{
	if (*hist)
		add_to_history(line, &((*hist)->next), ++id);
	else
	{
		push_back_history(hist, create_history(line, id);
		if (!(*hist = (t_hist *)malloc(sizeof(t_hist))))
			error_exit(sh, mem_alloc_err);
		(*hist)->id = id;
		(*hist)->line = ft_strdup(line);
		(*hist)->bytes_str = ft_strdup(g_info->bytes_quote_str);
		(*hist)->next = 0;
		(*hist)->prev = start;
		g_info->hist_counter++;
	}
}*/
