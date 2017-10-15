/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 20:33:41 by opodolia          #+#    #+#             */
/*   Updated: 2017/07/16 14:50:30 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_quote(char *str, unsigned int *i)
{
	if ((str[*i] == 34 || str[*i] == 39) &&
			valid_quote(str, *i + 1, str[*i]) != -1)
		*i = valid_quote(str, *i + 1, str[*i]);
	str[*i] ? (*i)++ : 0;
}

int		count_commands(char *str, char sign)
{
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && str[i] == sign)
			i++;
		if (str[i])
			count++;
		while (str[i] && str[i] != sign)
			check_quote(str, &i);
	}
	return (count);
}

char 	*separate_line(char *line, unsigned int *i, char sign)
{
	unsigned int	start;

	while (line[*i] && line[*i] == sign)
		(*i)++;
	start = *i;
	while (line[*i] && line[*i] != sign)
		check_quote(line, i);
	return (ft_strsub(line, start, (size_t)(*i - start)));
}

void	separate_pipes(t_pipe *p, char *cmd)
{
	int				i;
	unsigned int	j;
	char			*sub_cmd;

	i = -1;
	j = 0;
	p->i = -1;
	if (!(p->pipe_cmds = (char **)ft_memalloc(sizeof(char *) *
		(count_commands(cmd, '|') + 1))))
			error_exit(sh, mem_alloc_err);
	while (++i < count_commands(cmd, '|'))
	{
		sub_cmd = separate_line(cmd, &j, '|');
		if(sub_cmd != NULL && ft_strlen(sub_cmd) > 0)
			p->pipe_cmds[++(p->i)] = ft_strdup(sub_cmd);
		ft_memdel((void **)&sub_cmd);
	}
	ft_memdel((void **)&cmd);
	if (p->i > 0)
		p->pipe_found = true;
}

int		split_line(char *line, t_env **env_info, t_hist **hist, t_pipe *p)
{
	char			*cmd;
	unsigned int	i;
	int				numb;
	int				j;
	int				status;

	i = 0;
	numb = -1;
	status = 1;
	while (++numb < count_commands(line, ';'))
	{
		cmd = separate_line(line, &i, ';');
		j = -1;
		while (cmd[++j])
			if (cmd[j] == '$' && cmd[j + 1] && ft_isalnum(cmd[j + 1]))
				cmd = parse_dollar(cmd, j, *env_info);
		separate_pipes(p, cmd);
		status = pipe_execute(p, env_info, hist);
		status = main_execute(p, env_info, hist);
		clean_up(p->pipe_cmds);
	}
	restore_fds();
	return (status);
}