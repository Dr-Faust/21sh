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

void	clean_up(char **args)
{
	int		i;

	i = -1;
	if (args && *args)
		while (args[++i])
			ft_memdel((void **)&args[i]);
	ft_memdel((void **)&args);
}

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

int		split_line(char *line, t_env **env_info, t_hist *hist)
{
	char			*cmd;
	unsigned int	i;
	int				numb;
	int				j;
	int				status;
	char 			*sub_cmd;
	int				numb_2;
	unsigned int	k;
	int				n;
	char 			**pipe_cmds;
	bool			pipe_exist;

	i = 0;
	numb = -1;
	status = 1;
	pipe_exist = false;
	while (++numb < count_commands(line, ';'))
	{
		cmd = separate_line(line, &i, ';');
		j = -1;
		while (cmd[++j])
			if (cmd[j] == '$' && cmd[j + 1] && ft_isalnum(cmd[j + 1]))
				cmd = parse_dollar(cmd, j, *env_info);
		


		if (!(pipe_cmds = (char **)ft_memalloc(sizeof(char *) *
			(count_commands(cmd, '|') + 1))))
			error_exit(sh, mem_alloc_err);
		k = 0;
		numb_2 = -1;
		n = -1;
		while (++numb_2 < count_commands(cmd, '|'))
		{
			sub_cmd = separate_line(cmd, &k, '|');
			if(sub_cmd != NULL && ft_strlen(sub_cmd) > 0)
				pipe_cmds[++n] = ft_strdup(sub_cmd);
			ft_memdel((void **)&sub_cmd);
		}
		ft_memdel((void **)&cmd);
		if (n > 0)
			pipe_exist = true;


		status = pipe_execute(pipe_cmds, n, env_info, hist, pipe_exist);
		status = main_execute(pipe_cmds, n, env_info, hist, pipe_exist);
		clean_up(pipe_cmds);
		restore_fds();
	}
	return (status);
}
