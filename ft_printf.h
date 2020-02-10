/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:07:38 by iwillens          #+#    #+#             */
/*   Updated: 2020/02/10 14:33:28 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "./libft/libft.h"
# include <stdarg.h>

# ifndef T_UNSIGNED
#  define T_UNSIGNED 0
#  define T_SIGNED 1
# endif

# ifndef PF_SPECIFIERS
#  define PF_SPECIFIERS_P "cspdiuxX%"
#  define PF_SPECIFIERS_B "cspdiuxX%nfge"
#  define PF_SPECIFIERS "%npscGgEeFfXxoudi"
# endif

# ifndef PF_SPEC_LLONG
#  define PF_SPEC_INT "di"
#  define PF_SPEC_UINT "upoxX"
#  define PF_SPEC_LLONG "p"
#  define PF_SPEC_DOUBLE "fFeEgGaA"
#  define PF_SPEC_NPOINTER "n"
# endif

# ifndef PF_WC_SET
#  define PF_WC_SET 0
#  define PF_WC_AP 1
#  define PF_WC_DEFAULT 2
# endif

# ifndef PF_FLAGS
#  define PF_FLAGS "-+ #0"
#  define PF_FLAG_MINUS 1
#  define PF_FLAG_PLUS  2
#  define PF_FLAG_SPACE 4
#  define PF_FLAG_SHARP 8
#  define PF_FLAG_ZERO 16
# endif

# ifndef M_I
#  define M_I 0xFFFFFFFF
#  define M_CHR 0xFF
#  define M_SHRT 0xFFFF
#  define M_LLI 0xFFFFFFFFFFFFFFFF
#  define M_UI 0xffffffffU
#  define M_UCHR 0xffU
#  define M_USHRT 0xffffU
#  define M_ULLI 0xffffffffffffffffU
# endif

/*
** Length Modifiers
** put as binary to check later on if certain modifier is allowed
*/

# ifndef LENGTH_MODIFIERS
#  define LENGTH_MODIFIERS "Ltzjlh"
#  define LM_LONG 1
#  define LM_LONGLONG 2
#  define LM_SHORT 4
#  define LM_CHAR 8
#  define LM_INTMAX 16
#  define LM_SIZE_T 32
#  define LM_PTRDIFF 64
#  define LM_LONGDBL 128
# endif

# ifndef TSTRING
#  define TSTRING 1
# endif

# ifndef TPLACEHOLDER
#  define TPLACEHOLDER 2
# endif

typedef long long int			t_ptrdiff;
typedef unsigned long long int	t_ulli;
typedef long long int			t_lli;

/*
** precision number, wildcard and if it was originally negative,
** as it is turned into positive on runtime
*/

typedef struct	s_contwidth
{
	int			nb;
	short		wc;
	int			was_negative;
}				t_contwidth;

/*
** the following struct, which is a LINKED LIST  is the heart of the function.
** It stores all strings, types, flags, converted values, making it ready
** to be printed.
** --> [type] can be cspdiuxX% (and bonus: nfge)
** 		if no type is specified (which means we're dealing with a string
**		in the body of the function first argument (str) which won't be
**		formatted, an arbitrary type "!" is given, and only the
**		prt_v is filled, indicating that this field is ready to be
**		printed.
** --> [flags] can be - 0 . * (and minimum field width)
** 		(l ll h hh for bonus, as well as # and +)
** --> [width], in case it is specified
** --> [value], the original value of the identifier
** --> [prt_v], the original value already treated using flags and
**		types and any conversion required.
** --> [orig_content] the full string of the identifier (or pure string);
*/

typedef struct	s_content
{
	char				*orig_content;
	void				*value;
	char				type;
	int					flags;
	int					length;
	t_contwidth			width;
	t_contwidth			prec;
	char				*prt_v;
	char				pad_chr;
	struct s_content	*next;
}				t_content;

/*
** main function
*/

int				ft_printf(const char *str, ...);

/*
** error handling
** should be improved in the future, as printf errors are sent
** as warnings to the compiler.
*/

void			pf_strerr_unterminated();
void			pf_strerr_invalidspecifier(char expected, char found);

/*
** content handling
*/

int				pf_getcontent(const char *str, t_list **items);
size_t			pf_countliststr(t_list **lst);
void			pf_getvaarg(va_list ap, t_list **items);

/*
** flags handling
** called by the content handler to fill the struct
** with the right flags, width, height, specifiers
*/

size_t			pf_getflags(char *str, int *flags);
size_t			pf_getwidth(char *str, int *number);
size_t			pf_getlength(char*str, int *length);
void			pf_flags_add(t_content *cnt);
void			pf_flags_padding(t_content *cnt);

/*
** content conversion
*/

void			pf_convert_integer(t_content *content, short type, size_t base);
void			pf_convert_content(t_content *content);
void			pf_convertlist(t_list **lst);
void			pf_convert_integer(t_content *cnt, short type, size_t base);
void			pf_convert_uinteger(t_content *cnt, short type, size_t base);
void			pf_convert_shortest_floatmant(t_content *cnt);
void			pf_convert_mantissa(t_content *cnt);
void			pf_convert_float(t_content *cnt);

/*
** strings
*/

char			*ft_chr_unicode(wchar_t c, int limit_1);
void			pf_writecharstr(char *s);
char			*pf_strchecknull(char *str);

/*
** memory
*/

void			pf_fillblank(t_content **content);
void			pf_freelist(t_list **lst);

#endif
