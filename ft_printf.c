/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/* i                                               +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:06:07 by iwillens          #+#    #+#             */
/*   Updated: 2020/01/31 23:32:35 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#include <unistd.h>
#ifndef PF_SPECIFIERS 
# define PF_SPECIFIERS_P "cspdiuxX%" //PADRAO
# define PF_SPECIFIERS_B "cspdiuxX%nfge" //BONUS
# define PF_SPECIFIERS "%npscAaGgEeFfXxoudi" //BONUS_EXTENDED
#endif

#ifndef PF_FLAGS
# define PF_FLAGS "-+ #0"
# define PF_FLAG_MINUS 1 // 00000001
# define PF_FLAG_PLUS  2 // 00000010
# define PF_FLAG_SPACE 4 // 00000100
# define PF_FLAG_SHARP 8 // 00001000
# define PF_FLAG_ZERO 16 // 00010000
#endif


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

#ifndef LENGHT_MODIFIERS
# define LENGHT_MODIFIERS "Ltzjlh"
# define LM_LONG 1
# define LM_LONGLONG 2
# define LM_SHORT 4
# define LM_CHAR 8
# define LM_INTMAX 16
# define LM_SIZE_T 32
# define LM_PTRDIFF 64
# define LM_LONGDBL 128
#endif

#ifndef TSTRING
# define TSTRING 1
#endif

#ifndef TPLACEHOLDER
# define TPLACEHOLDER 2
#endif


/*
** the following struct, which is a LINKED LIST  is the heart of the function. 
** It stores all strings, types, flags, converted values, making it ready
** to be printed.
** --> [type] can be cspdiuxX% (and bonus: nfge)
** 		if no type is specified (which means we're dealing with a string
**		in the body of the function first argument (str) which won't be
**		formatted, an arbitrary type "!" is given, and only the printable_value
**		is filled, indicating that this field is ready to be printed.
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
	long				bflags;
	t_contwidth			width;
	t_contwidth			precision;
	char				*printable_value;
	struct s_content	*next;
}				t_content;

void pf_unterminated_strerr()
{
	ft_putstr_fd("**** UNTERMINATED!!! What now?!?! ***\n",1 );
}
size_t pf_getflags(char *str, short *flags)
{
	size_t pos;

	pos = 0;
	*flags = 0;
	str++;
	while (*str)
	{
		if(*str == '-')
			*flags |= PF_FLAG_MINUS;	
		else if(*str == '+')
			*flags |= PF_FLAG_PLUS;	
		else if(*str == ' ')
			*flags |= PF_FLAG_SPACE;	
		else if(*str == '#')
			*flags |= PF_FLAG_SHARP;	
		else if(*str == '0')
			*flags |= PF_FLAG_ZERO;	
		else
			return (pos);
		pos++;
		str++;
	}
	return pos;
}

size_t pf_getwidth(char *str, int *number)
{
	size_t	pos;
	char	*nbstr;

	pos = 0;
	*number = 0;
	while (ft_isdigit(str[pos]))
		pos++;
	if (pos != 0)
	{
		nbstr = (char*)malloc(sizeof(char) * (pos + 1));
		ft_memcpy(nbstr, str, pos);
		nbstr[pos] = '\0';
		*number = ft_atoi(nbstr);
		free(nbstr);
	}


	return (pos);
}
size_t pf_getlength(char*str, short *length)
{
	size_t pos;

	pos = 0;
	*length = 0;
		if(*str == 'l')
		{
			if(str[1] == 'l')
				*length |= LM_LONGLONG;
			else
				*length |= LM_LONG;	
		}
		else if(*str == 'h')
		{
			if(str[1] == 'h')
				*length |= LM_CHAR;
			else
				*length |= LM_SHORT;	
		}
		else if(*str == 'j')
			*length |= LM_INTMAX;	
		else if(*str == 'z')
			*length |= LM_SIZE_T;	
		else if(*str == 't')
			*length |= LM_PTRDIFF;	
		else if(*str == 'L')
			*length |= LM_LONGDBL;	
		else
			return (pos);
		pos++;
		if (*length & LM_LONGLONG || *length & LM_CHAR)
			pos++;
		return pos;
	
}	
void pf_fillcontent(char *str, t_content **content)
{
	short	flags;
	int		number;

	str+=pf_getflags(str, &flags) + 1;
	(*content)->flags = flags;
	str+=pf_getwidth(str, &number);
	(*content)->width.number = number;
	if (number == 0 && *str == '*')
		(*content)->width.wildcard = 1;
	else
		(*content)->width.wildcard = 0;
	if (*str == '.')
	{
		str++;
		str+=pf_getwidth(str, &number);
		(*content)->precision.number = number;
		if (number == 0 && *str == '*')
			(*content)->precision.wildcard = 1;
		else
			(*content)->precision.wildcard = 0;
	}
	str+=pf_getlength(str, &(*content)->length);
	if (*str != (*content)->type)
	{
		write(1, "ERRO: Identificador não conhecido-->",37); /// GERENCIAR ERRO	
		ft_putchar_fd((*content)->type,1);
		ft_putchar_fd(*str, 1);
		ft_putstr_fd("\n", 1);
	}
}

/*
** 1 = string
** 2 = indicator
*/
void pf_additem(t_list **items, char *str, int type)
{
	t_content *content;
	content = (t_content*)malloc(sizeof(t_content));
	content->orig_content = str;
	if (type == TSTRING)
		content->type = '!';
	else
	{
		content->type = str[ft_strlen(str) - 1]; 
		pf_fillcontent(str, &content);
	}
	ft_lstadd_back(items, ft_lstnew(content));
}

size_t	pf_getcontent_string(const char *str, size_t pos, t_list **items, int type)
{
	char	*string;

	string = ft_strndup(str, pos);
	pf_additem(items, string, type);
	return (pos);
}

/*
** gets the content  
*/

int pf_getcontent(const char *str, t_list **items)
{
	size_t pos;

	while (*str)
	{
		pos = 0;
		if (*str == '%')
		{
			pos = ft_strfind_first(&str[1], PF_SPECIFIERS);
			if (pos == 0)
				pf_unterminated_strerr();
			else
				str+=pf_getcontent_string(str, pos, items, TPLACEHOLDER);
		}
		else
		{
			if (!(pos = ft_strfind_first(str, "%") ))
				pos = ft_strlen(str) - 1;
			else
				pos-=2;
			str+=pf_getcontent_string(str, pos, items, TSTRING);
		}
			str++;
	}
		return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list		ap;
	const char	*string;
	t_list		*items;
   	items = NULL;

	string = str;
	va_start(ap, str);
	int i;
	i = 0;
	pf_getcontent(str, &items);

	t_content *cnt;
	t_list *head;
	head = items;
	write(1, "**types:\n",9); 
	while(items)
	{
		cnt = (t_content*)((items->content));
		ft_putchar_fd(cnt->type,1);
		items = items->next;
		write(1, "\n", 1);
	}
	items = head;

	write(1, "**values:\n",10); 
	while(items)
	{
		cnt = (t_content*)((items->content));
		ft_putstr_fd(cnt->orig_content,1);
		items = items->next;
		write(1, "\n", 1);
	}
	items = head;



	while (i < 2)
	{
		int c;
	   	c = va_arg(ap, int);
		ft_putnbr_fd(c, 1);
		i++;
	}

		
	va_end(ap);
	return 0;
}
