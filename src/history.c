/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 16:19:21 by opodolia          #+#    #+#             */
/*   Updated: 2017/08/30 17:15:46 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_history(t_hist *hist)
{
	if (!(hist = (t_hist *)malloc(sizeof(t_hist))))
		error_exit(sh, mem_alloc_err);

}

void		add_to_history(t_hist *hist)
{
		
	if (hist)
		add_to_history(&(hist->next));
	else
		create_history(hist);
}

t_hist	*p_hist;
	t_hist	*new;
	int		last_id;

	if (!(s->rcmd))
		return (s);
	p_hist = s->history;
	last_id = p_hist->id;
	if (last_id == 0)
	{
		p_hist->cmd = ft_strdup(s->rcmd);
		p_hist->id = 1;
		s->index = 1;
		return (s);
	}
	if (!(new = (t_hist *)malloc(sizeof(t_hist))))
		return (NULL);
	new->id = last_id + 1;
	new->cmd = ft_strdup(s->rcmd);
	new->next = p_hist;
	s->history = new;
	s->index = new->id;
	return (s);
