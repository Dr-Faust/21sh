/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 12:03:22 by opodolia          #+#    #+#             */
/*   Updated: 2017/06/13 18:03:26 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "../libft/includes/libft.h"

/*
**				== Regular font colors ==
*/

# define DEF		"\033[0m"
# define BLACK		"\033[30m"
# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define MAGENTA	"\033[35m"
# define CYAN		"\033[36m"
# define GREY		"\033[37m"

/*
**				== Bold font colors ==
*/

# define B_DEF		"\033[0;39m"
# define B_BLACK	"\033[1;30m"
# define B_RED		"\033[1;31m"
# define B_GREEN	"\033[1;32m"
# define B_YELLOW	"\033[1;33m"
# define B_BLUE		"\033[1;34m"
# define B_MAGENTA	"\033[1;35m"
# define B_CYAN		"\033[1;36m"
# define B_GREY		"\033[1;37m"

/*
**				== Background colors ==
*/

# define DG_DEF		"\033[49m"
# define BG_BLACK	"\033[40m"
# define BG_RED		"\033[41m"
# define BG_GREEN	"\033[42m"
# define BG_YELLOW	"\033[43m"
# define BG_BLUE	"\033[44m"
# define BG_MAGENTA	"\033[45m"
# define BG_CYAN	"\033[46m"
# define BG_GREY	"\033[47m"

typedef enum
{
	none,
	hh,
	h,
	l,
	ll,
	j,
	z,
	L,
}	t_length;

typedef enum
{
	no,
	yes,
	o,
	x,
	X,
	b,
}	t_hash;

typedef struct	s_flags
{
	int			left;
	int			plus;
	int			space;
	t_hash		hash;
	int			zero;
	int			unread;
	int			quote_mark;
}				t_flags;

typedef struct	s_mods
{
	t_flags		flags;
	int			width;
	int			precision;
	t_length	length;
	char		qualifier;
	int			base;
	int			sigfig;
	int			exp_base;
	char		exp_char;
	int			exp_len;
}				t_mods;

int				ft_printf(const char *format, ...);
int				ft_flags(const char *format, t_mods *mods);
int				ft_width(const char *format, t_mods *mods, va_list ap);
int				ft_precision(const char *format, t_mods *mods, va_list ap);
int				ft_length(const char *format, t_mods *mods);
int				ft_qualifier(char c, t_mods *mods);

int				ft_no_qual(t_mods *mods);
int				ft_numb(va_list ap, t_mods *mods);
int				ft_char(va_list ap, t_mods *mods);
int				ft_str(va_list ap, t_mods *mods);
int				ft_float(va_list ap, t_mods *mods);

int				ft_size(char *str, t_mods *mods);
int				ft_is_mb(char *s);
char			*ft_convert_len(va_list ap, t_mods *mods, char c);
char			*ft_convert_ulen(va_list ap, t_mods *mods, char c);
void			ft_push_right(t_mods *mods, char **mas, int size, char *str);
void			ft_push_left(t_mods *mods, char **mas, int size, char *str);
char			*ft_ftoa_handler(long double n, t_mods *mods, char c);
long double		ft_get_mantissa(long double n, int base);
int				ft_put_sign(t_mods *mods, char **mas, int i, char *str);
int				ft_put_content(t_mods *mods, char **mas, int i, char *str);
char			*ft_unprint(char *s, int i);
char			*ft_quote_mark(char *str);

#endif
