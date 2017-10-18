/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 15:09:50 by opodolia          #+#    #+#             */
/*   Updated: 2017/09/14 21:12:25 by opodolia         ###   ########.fr       */
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
# include <ncurses.h>
# include <stdbool.h>
# include <fcntl.h>

# define PATH_LEN			1024

/*
**							    ==[ Keys definition ]==
*/

# define LEFT				'D'
# define RIGHT				'C'
# define UP					'A'
# define DOWN				'B'
# define START				'H'
# define END				'F'
# define DELETE				'~'
# define BACKSPACE			127
# define CTRL_D				4

/*
**							  ==[ Redirection structure ]==
*/

typedef struct		s_redirect
{
	bool			write_found;
	bool			append_found;
	bool			read_found;
	bool			heredoc_found;
	int 			write_index;
	int 			append_index;
	int 			read_index;
	char 			*heredoc_line;
}					t_redirect;

/*
**								 ==[ Pipe structure ]==
*/

typedef struct		s_pipe
{
	char			**pipe_cmds;
	bool			pipe_found;
	int 			index;
	int 			fds[2];
	int 			input;
	t_redirect		*r;
}					t_pipe;

/*
**							 ==[ Environment structure ]==
*/

typedef struct		s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}					t_env;

/*
**							   ==[ History structure ]==
*/

typedef struct		s_hist
{
	unsigned int	id;
	char			*line;
	struct s_hist	*next;
	struct s_hist	*prev;
}					t_hist;

/*
**							 ==[ Global info structure ]==
*/

typedef struct		s_glob_info
{
	struct termios	default_term;
	struct winsize	win;
	unsigned short	prompt_len;
	unsigned short	win_width;
	unsigned short	win_height;
	char			*line;
	char			*quote_line;
	unsigned short	bytes;
	unsigned short	row_position;
	unsigned int	position;
	unsigned int	index;
	unsigned int	hist_counter;
	short			hist_search_flag;
	char			*hist_start_line;
	int				stdin_fd_copy;
	int				stdout_fd_copy;
	int 			stderr_fd_copy;
	char 			*marker;
}					t_glob_info;

extern t_glob_info	*g_info;

/*
**							   ==[ Errors with exit ]==
*/

typedef enum
{
	mem_alloc_err,
	setup_term_err,
}	t_err_exit;

/*
**							  ==[ Errors with return 1 ]==
*/

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
	no_such_var,
	err_cal_fork,
	incorrect_param,
	chld_proc_not_crtd,
}	t_err_ret;

/*
**						 ==[ Errors in setting up terminal ]==
*/

typedef enum
{
	err_sys,
	err_dump,
}	t_sig_err;

/*
**					   ==[ Commands list for printing errors ]==
*/

typedef enum
{
	sh,
	cd,
	env,
	set_env,
	unset_env,
}	t_command;

/*
**									==[ Main ]==
*/

void				set_terminal();
unsigned short		get_curr_row_position(void);
void				restore_fds(void);


/*
**								 ==[ Environment ]==
*/

t_env				*get_env_info(char **arr);
void				clean_env_info(t_env **env_info);
char				*get_env_var(char *var, t_env *env_info);
char				**env_to_arr(t_env *env_info);

/*
**								   ==[ Prompt ]==
*/

int					check_prompt(short data);
int					write_prompt(void);

/*
**								 ==[ Line reader ]==
*/

char				*read_line(t_hist **hist);
void				parse_keys(char *buf, bool *flag, t_hist **hist,
					unsigned int *hist_counter);

/*
**								   ==[ Parser ]==
*/

int					parse_line(char *line, t_env **env_info, t_hist **hist);
int					split_line(char *line, t_env **env_info, t_hist **hist,
					t_pipe *p);
void				reset_flags(t_pipe *p);
char 				*separate_line(char *line, unsigned int *i, char sign);
char				**split_command(char *line);
char				*parse_quotes(char *line, t_hist **hist);
int					valid_quote(char *s, unsigned int i, char quote);
char				*parse_dollar(char *line, unsigned int i, t_env *env_info);
int					count_args(char *str);
int					count_commands(char *str, char sign);

/*
**								 ==[ Execution ]==
*/

int					builtins_handler(char **args, t_env **env_info,
					t_hist *hist);
char				*treat_path(char **args, t_env *env_info);
char				*verif_access(char *command, t_env *env_info);
int					main_execute(t_pipe *p, t_env **env_info, t_hist **hist);
int 				execute(t_pipe *p, t_env **env_info, t_hist **hist);
int					launch(char **args, t_env *env_info, t_pipe *p, char *path);
int					heredoc_launch(char **args, t_env *env_info, t_pipe *p);
void				clean_up(char **args);

/*
**							    ==[ Redirections ]==
*/

int					check_redirections(char **args, t_hist **hist, t_pipe *p);
int					manage_heredoc(char **args, t_hist **hist, t_pipe *p, int *index);
int 				set_write_fd(char **args, int index);
int					set_append_fd(char **args, int index);
int					set_read_fd(char **args, int index);
void				set_pipe_fd(t_pipe *p);
void				set_heredoc_fd(t_pipe *p);

/*
**							 ==[ Built in functions ]==
*/

int					ft_echo(char **args);
int					ft_cd(char **args, t_env **env_info);
int					ft_env(char **args, t_env *env_info);
int					ft_setenv(t_env **env_info, char *var, char *value,
					char **args);
int					ft_unsetenv(t_env *env_info, char *var);
int					ft_help(void);

/*
**							  ==[ Cursor movement ]==
*/

void				left_arrow(char *buf);
void				right_arrow(char *buf);
void				up_arrow(char *buf, t_hist *hist,
					unsigned int *hist_counter);
void				down_arrow(char *buf, t_hist **hist,
					unsigned int *hist_counter);
void				move_left(void);
void				extended_move_left(unsigned int line_indx);
void				move_right(void);

/*
**							   ==[ Line edition ]==
*/

char				*add_char(char *buf);
char				*del_char(char *buf);

/*
**								  ==[ Errors ]==
*/

void				error_exit(t_command command_type, t_err_exit error_type);
int					error_return(t_command command_type, t_err_ret error_type,
					char *arg);
int					signal_error(t_command command_type, t_sig_err error_type,
					char *arg);

/*
**								  ==[ Signals ]==
*/

void				manage_signals(void);
int					prompt_flag(short data);

/*
**								  ==[ History ]==
*/

void				add_to_history(char *line, t_hist **hist, t_env *env_info,
					unsigned int id);
void				add_prev_elem(t_hist **hist);
void				print_prev_hist(t_hist *hist, unsigned int *hist_counter);
void				print_next_hist(t_hist *hist, unsigned int *hist_counter);
bool				print_history(t_hist *hist);
unsigned int		get_position(unsigned int line_indx);
void				add_line_to_history_file(char *line, t_env *env_info);

#endif
