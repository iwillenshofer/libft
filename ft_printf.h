/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:07:38 by iwillens          #+#    #+#             */
/*   Updated: 2020/02/04 18:43:03 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>

# ifndef T_UNSIGNED
#  define T_UNSIGNED 0
#  define T_SIGNED 1
# endif

# ifndef PF_SPECIFIERS 
#  define PF_SPECIFIERS_P "cspdiuxX%" //PADRAO
#  define PF_SPECIFIERS_B "cspdiuxX%nfge" //BONUS
#  define PF_SPECIFIERS "%npscAaGgEeFfXxoudi" //BONUS_EXTENDED
# endif

# ifndef PF_SPEC_LLONG
#  define PF_SPEC_LLONG "diuoxX"
#  define PF_SPEC_DOUBLE "fFeEgGaA"
# endif
# ifndef PF_WILDCARD_SET
#  define PF_WILDCARD_SET 0
#  define PF_WILDCARD_AP 1
#  define PF_WILDCARD_DEFAULT 3
# endif
# ifndef PF_FLAGS
#  define PF_FLAGS "-+ #0"
#  define PF_FLAG_MINUS 1 // 00000001
#  define PF_FLAG_PLUS  2 // 00000010
#  define PF_FLAG_SPACE 4 // 00000100
#  define PF_FLAG_SHARP 8 // 00001000
#  define PF_FLAG_ZERO 16 // 00010000
# endif

/*
** Lenght Modifiers
** put as binary to check later on if certain modifier is allowed
** within a certain specifier.
** 1 = l
** 2 = ll
** 4 = h
** 8 = hh
** 16 = j
** 32 = z
** 64 = t
** 128 = L
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

/*
** the following struct, which is a LINKED LIST  is the heart of the function. 
** It stores all strings, types, flags, converted values, making it ready
** to be printed.
** --> [type] can be cspdiuxX% (and bonus: nfge)
** 		if no type is specified (which means we're dealing with a string
**		in the body of the function first argument (str) which won't be
**		formatted, an arbitrary type "!" is given, and only the
**		printable_value is filled, indicating that this field is ready to be
**		printed.
** --> [flags] can be - 0 . * (and minimum field width)
** 		(l ll h hh for bonus, as well as # and +) 
** --> [width], in case it is specified 
** --> [value], the original value of the identifier
** --> [printable_value], the original value already treated using flags and
**		types and any conversion required.
** --> [orig_content] the full string of the identifier (or pure string);
*/

typedef struct	s_contwidth
{
	size_t	number;
	short	wildcard;
}				t_contwidth;

typedef struct	s_content
{
	char				*orig_content;
	void				*value;
	char				type;
	short				flags;
	short				length;
	t_contwidth			width;
	t_contwidth			precision;
	char				*printable_value;
	char				padding_char;
	struct s_content	*next;
}				t_content;

int ft_printf(const char *, ...);

/*
** error handling
*/

void pf_strerr_unterminated();
void pf_strerr_invalidspecifier(char expected, char found);

/*
** content handling
*/

int pf_getcontent(const char *str, t_list **items);

/*
** flags handling
** called by the content handler to fill the struct
** with the right flags, width, height, specifiers
*/

size_t pf_getflags(char *str, short *flags);
size_t pf_getwidth(char *str, int *number);
size_t pf_getlength(char*str, short *length);

/*
** content conversion
**
*/

void pf_convert_integer(t_content *content, short type, size_t base);
void pf_convert_content(t_content *content);
void pf_convertlist(t_list **lst);


#endif
