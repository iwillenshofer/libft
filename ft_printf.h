/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:07:38 by iwillens          #+#    #+#             */
/*   Updated: 2024/05/30 17:02:31 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <stddef.h>

# define PRINTF_BUFFER_SIZE 4096
# define PRINFT_BUFFERNB_SIZE 96

# define PRINTF_FAILURE -1
# define PRINTF_SUCCESS 0
# define ERR_UNTERMINATED_SPEC "unterminated specifier\n"
# define ERR_PRINTINGERROR "printing failed\n"

# define STR_NULL "(null)"

# define PF_BASE_10 "0123456789"
# define PF_BASE_16 "0123456789abcdef"
# define PF_BASE_16U "0123456789ABCDEF"

#  define PF_SPECIFIERS "cspdiuxX%"
#  define PF_SPEC_INT "dic"
#  define PF_SPEC_UINT "uxX"
#  define PF_SPEC_PTR "p"
#  define PF_SPEC_STR "s"
#  define PF_SPEC_CHAR "%"

/*
** defines WIDTH/PRECISION:
** wether there is none, it is set in the string
** or it is a wildcard to be set with va_arg
*/
# ifndef PF_WC_SET
#  define PF_WC_DEFAULT 0
#  define PF_WC_SET 1
#  define PF_WC_AP 2
# endif

# ifndef PF_FLAGS
#  define PF_FLAGS "-+ #0"
#  define PF_FLAG_MINUS 1
#  define PF_FLAG_PLUS  2
#  define PF_FLAG_SPACE 4
#  define PF_FLAG_SHARP 8
#  define PF_FLAG_ZERO 16
# endif

/*
** precision number, wildcard and if it was originally negative,
** as it is turned into positive on runtime
*/

typedef struct s_contwidth
{
	size_t		nb;
	size_t		wc;
	int			was_negative;
}	t_contwidth;

typedef union u_data {
    char				*s;
	long long			i;
	unsigned long long	u;
}	t_data;

/*
** the following struct is used to store the information about the
** conversion, during printing.
*/
typedef struct s_prtinfo
{
	size_t		num_len;
	size_t		padding_len;
	size_t		precision_len;
	char		padding_char;
	char		signal_char;
	int			sign;
	char		prepend[3];
	char		*base;
}	t_prtinfo;

typedef struct s_content
{
	char				type;
	size_t 				pos;
	size_t				counter;
	t_data				value;
	t_prtinfo			prt;
	int					error;
	int					flags;
	t_contwidth			width;
	t_contwidth			prec;
}	t_content;

typedef struct s_printf
{
	char			buffer[PRINTF_BUFFER_SIZE];
	size_t			buffer_pos;
	t_content		cnt;
	int				fd;
	char			*str;
	size_t			counter;
}	t_printf;

/*
** main function
*/

int				ft_printf(const char *str, ...);
void			process_int(t_printf *printf);
void			process_uint(t_printf *printf);
void			process_string(t_printf *printf);
void 			process_char(t_printf *printf);
void			get_values(va_list *ap, t_content *content);

/*
** print.c
*/
ssize_t			printchar(char c, t_printf *printf);
ssize_t			printnchar(char c, int n, t_printf *printf);
ssize_t			printnstr(char *str, int n, t_printf *printf);
ssize_t			printstr(char *str, t_printf *printf);
ssize_t			printnumber(long long n, char *base, t_printf *printf);

/*
** buffer.c
*/
void			dump_buffer(t_printf *printf);
void			dump_if_needed(t_printf *printf);

/*
** error handling
*/
int				fatal(char *msg, int silent);
int				fatal_specifier(char expected, char found);

/*
** flags handling
*/

size_t			getflags(const char *str, int *flags);
size_t			getwidth(const char *str, int *number);

#endif
