/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 15:09:50 by opodolia          #+#    #+#             */
/*   Updated: 2017/08/18 21:19:25 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft_printf/includes/ft_printf.h"
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <term.h>
# include <pwd.h>
# include <sys/stat.h>
# include <termcap.h>
# include <signal.h>

# define PATH_LEN			1024

# define LEFT				'D'
# define RIGHT				'C'
# define UP					'A'
# define DOWN				'B'
# define START				'H'
# define END				'F'
# define DELETE				'~'
# define BACKSPACE			127

typedef struct		s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}					t_env;

typedef struct		s_win
{
	struct winsize	win_size;
	int				prompt_len;
	int				position;
	int				index;
	int				flag;
	char			*bytes_str;
	int				i;
	int				bytes;
}					t_win;

//struct t_win		w;

struct termios		default_term;
struct winsize		win_size;
int					g_win_size;
char				*g_line;

typedef enum
{
	mem_alloc_err,
	setup_term_err,
}	t_err_exit;

typedef	enum
{
	home_not_set,
	oldpwd_not_set,
	no_s_f_or_dir,
	perm_denied,
	com_not_found,
	too_few_args,
	too_much_args,
	not_an_id,
	too_few_args_u,
	no_such_var,
	err_cal_fork,
}	t_err_ret;

typedef enum
{
	err_sys,
	err_dump,
}	t_sig_err;

typedef enum
{
	sh,
	cd,
	set_env,
	unset_env,
}	t_command;

void				set_terminal();
t_env				*get_env_info(char **arr);
int					check_prompt(int data);
int					write_prompt();
char				*read_line(t_win *w);
int					split_line(char *line, t_env **env_info, int status,
					char ***args);
char				**split_command(char *line);
char				*parser(char *line, t_win *w);
char				*parse_dollar(char *line, int i, t_env *env_info);
char				*get_env_var(char *var, t_env *env_info);
int					count_args(char *str);
int					count_commands(char *str);
int					valid_quote(char *s, int i, char quote);
int					execute(char **args, t_env **env_info);
char				**env_to_arr(t_env *env_info);
char				*verif_access(char *command, t_env *env_info);
int					lsh_num_builtins();
int					ft_echo(char **args);
int					ft_cd(char **args, t_env **env_info);
int					ft_env(t_env *env_info);
int					ft_setenv(t_env **env_info, char *var, char *value,
					char **args);
int					ft_unsetenv(t_env *env_info, char *var);
int					ft_help(void);

/*
**						== Cursor movement ==
*/

void				left_arrow(char *buf, t_win *w);
void				right_arrow(char *buf, t_win *w);
void				move_left(t_win *w);
void				move_right(t_win *w);
void				up_arrow(char *buf, t_win *w);
void				down_arrow(char *buf, t_win *w);

/*
**						 == Line edition ==
*/

char				*add_char(char *buf, t_win *w);
char				*del_char(char *buf, t_win *w);

/*
**						    == Errors ==
*/

void				error_exit(t_command command_type, t_err_exit error_type);
int					error_return(t_command command_type, t_err_ret error_type,
					char *arg);
int					signal_error(t_command command_type, t_sig_err error_type,
					char *arg);

/*
**						    == Sugnals ==
*/

void				manage_signal(void);
int					singleton_prompt(int data);

#endif
