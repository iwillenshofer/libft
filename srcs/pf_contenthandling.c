/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_contenthandling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 11:34:49 by iwillens          #+#    #+#             */
/*   Updated: 2024/05/29 14:27:04 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** helper for pf_fillcontent function. Checks whether there is a dot
** to define the precision flag.
*/

static char		*pf_fillcontent_checkdot(char *str, t_content **content,
	int number)
{
	if (*str == '.')
	{
		str++;
		str += pf_getwidth(str, &number);
		(*content)->prec.nb = number;
		if (number == 0 && *str == '*')
		{
			(*content)->prec.wc = PF_WC_AP;
			str++;
		}
		else
			(*content)->prec.wc = PF_WC_SET;
	}
	return (str);
}

/*
** go through the whole string passed by the user (%...s)
** to check for flags, width, precision, modifier and specifier.
*/
#include <stdio.h>
static void		pf_fillcontent(char *str, t_content **content)
{
	int		flags;
	int		number;

	str += pf_getflags(str, &flags) + 1;
	(*content)->flags = flags;
	str += pf_getwidth(str, &number);
	(*content)->width.nb = number;
	printf("NUMBER: %d\n", number);
	if (number == 0 && *str == '*')
	{
		(*content)->width.wc = PF_WC_AP;
		str++;
	}
	else if (number)
		(*content)->width.wc = PF_WC_SET;
	str = pf_fillcontent_checkdot(str, content, number);
	if (*str != (*content)->type)
		pf_strerr_invalidspecifier((*content)->type, *str);
}

/*
** 1 = string (!)
** 2 = indicator
** adds a struct to the list. If the content is just a string
** (not a specifier), it sets the specifier arbitrarily as '!'.
** in that case, no modifications will be necessary and
** it will be later on be printed and counted using
** content->orig_content instead of content->prt_v (printable value)
*/

static void		pf_additem(t_list **items, char *str, int type)
{
	t_content *content;

	content = (t_content*)malloc(sizeof(t_content));
	if (!content)
		return;
	content->orig_content = str;
	pf_fillblank(&content);
	if (type == TSTRING)
		content->type = '!';
	else
	{
		content->type = str[ft_strlen(str) - 1];
		pf_fillcontent(str, &content);
	}
	ft_lstadd_back(items, ft_lstnew(content));
}

/*
** duplicates the string, which will be added to the list through
** pf_additem.
*/

static size_t	pf_getcontent_string(const char *str,
						size_t pos, t_list **items, int type)
{
	char *string;

	string = ft_strndup(str, pos + 1);
	pf_additem(items, string, type);
	return (pos);
}

/*
** gets the content
*/

int				pf_getcontent(const char *str, t_list **items)
{
	size_t pos;

	while (*str)
	{
		pos = 0;
		if (*str == '%')
		{
			pos = ft_strfind_first(&str[1], PF_SPECIFIERS);
			if (pos == 0)
				pf_strerr_unterminated();
			else
				str += pf_getcontent_string(str, pos, items, TPLACEHOLDER);
		}
		else
		{
			if (!(pos = ft_strfind_first(str, "%")))
				pos = ft_strlen(str) - 1;
			else
				pos -= 2;
			str += pf_getcontent_string(str, pos, items, TSTRING);
		}
		str++;
	}
	return (0);
}
