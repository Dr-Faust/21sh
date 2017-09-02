#include "minishell.h"

static int	check_print_position(char *buf)
{
	if (buf[0] == '\n')
	{
		while (g_info->line[g_info->line_index])
			move_right();
		ft_printf("\n");
		g_info->line = ft_strjoin_free_first(g_info->line, "\n\0");
		return (1);
	}
	else if (g_info->line_index < (int)ft_strlen(g_info->line))
		g_info->line = add_char(buf);
	else
	{
		g_info->bytes_str = ft_strjoin_free(g_info->bytes_str,
				ft_itoa(g_info->bytes));
		g_info->line = ft_strjoin_free_first(g_info->line, buf);
		ft_printf("%s", buf);
	}
	g_info->line_index += g_info->bytes_str[g_info->bytes_index] - '0';
	g_info->position++;
	g_info->bytes_index++;
	return (0);
}

void		parse_keys(char *buf, int *flag, t_hist **hist, int *hist_counter)
{
	if (buf[2] == LEFT || buf[3] == LEFT || buf[2] == START)
		left_arrow(buf);
	else if (buf[2] == RIGHT || buf[3] == RIGHT || buf[2] == END)
		right_arrow(buf);
	else if (buf[2] == UP || buf[3] == UP)
		up_arrow(buf, *hist, hist_counter);
	else if (buf[2] == DOWN || buf[3] == DOWN)
		down_arrow(buf, hist, hist_counter);
	else if ((buf[0] == BACKSPACE && g_info->line_index > 0) ||
			(buf[3] == DELETE && g_info->line[g_info->line_index]))
		g_info->line = del_char(buf);
	else if (buf[0] == CTRL_D && !g_info->line[0])
	{
		*flag = 1;
		g_info->line = ft_strjoin_free_first(g_info->line, "exit");
		ft_putchar('\n');
	}
	else if (buf[0] != BACKSPACE && buf[3] != DELETE &&
			!ft_isunprint(buf[0]))
		*flag = check_print_position(buf);
}