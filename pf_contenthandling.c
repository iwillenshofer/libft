/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_contenthandling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 11:34:49 by iwillens          #+#    #+#             */
/*   Updated: 2020/02/04 22:06:21 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		pf_fillcontent(char *str, t_content **content)
{
	short	flags;
	int		number;

	str += pf_getflags(str, &flags) + 1;
	(*content)->flags = flags;
	str += pf_getwidth(str, &number);
	(*content)->width.number = number;
	if (number == 0 && *str == '*')
		(*content)->width.wildcard = 1;
	else
		(*content)->width.wildcard = 0;
	if (*str == '.')
	{
		str++;
		str += pf_getwidth(str, &number);
		(*content)->precision.number = number;
		if (number == 0 && *str == '*')
		{
			(*content)->precision.wildcard = PF_WILDCARD_AP;
			str++;
		}
		else
		{
			(*content)->precision.wildcard = PF_WILDCARD_SET;
		}
	}
	str += pf_getlength(str, &(*content)->length);
	if (*str != (*content)->type)
		pf_strerr_invalidspecifier((*content)->type, *str);
}

/*
** used to initialize the structs variables
** if its content is just a string (no specifiers)
*/

static void		pf_fillblank(t_content **content)
{
	(*content)->flags = 0;
	(*content)->width.number = 0;
	(*content)->width.wildcard = 0;
	(*content)->precision.number = 0;
	(*content)->padding_char = ' ';
	(*content)->precision.wildcard = PF_WILDCARD_DEFAULT;
}

/*
** 1 = string
** 2 = indicator
*/

static void		pf_additem(t_list **items, char *str, int type)
{
	t_content *content;

	content = (t_content*)malloc(sizeof(t_content));
	content->orig_content = str;
	if (type == TSTRING)
	{
		content->type = '!';
		pf_fillblank(&content);
	}
	else
	{
		content->type = str[ft_strlen(str) - 1];
		pf_fillblank(&content);
		pf_fillcontent(str, &content);
	}
	ft_lstadd_back(items, ft_lstnew(content));
}

static size_t	pf_getcontent_string(const char *str,
						size_t pos, t_list **items, int type)
{
	char *string;

	string = ft_strndup(str, pos);
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
