/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:06:07 by iwillens          #+#    #+#             */
/*   Updated: 2020/02/10 14:34:20 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

/*
** one of the last steps of ft_printf,
** goes through the linked list and prints it.
** it takes special care of two cases:
** 1. if a string is being printed (not passed as argument %s, but hardcoded)
** in first arg, it prints the orig_content instead of printable_value (prt_v)
** as it wasn't supposed to be changed.
** 2. if it is a char, it is treated as a special case, since it can be passed
** as null (and a null char should be printed). If it was printed normally,
** ft_putstr would have stopped at \0 and not printed anything
*/

void	pf_printlist(t_list **lst)
{
	t_content	*cnt;
	t_list		*tmp;

	tmp = *lst;
	while (tmp)
	{
		cnt = (tmp)->content;
		if (cnt->type == '!')
			ft_putstr_fd(cnt->orig_content, 1);
		else if (cnt->type == 'c' && *(wchar_t*)cnt->value == 0)
			pf_writecharstr(cnt->prt_v);
		else
			ft_putstr_fd(cnt->prt_v, 1);
		(tmp) = (tmp)->next;
	}
}

/*
** the main function.
*/

int		ft_printf(const char *str, ...)
{
	va_list		ap;
	t_list		*items;
	size_t		counter;

	items = NULL;
	pf_getcontent(str, &items);
	va_start(ap, str);
	pf_getvaarg(ap, &items);
	va_end(ap);
	pf_convertlist(&items);
	pf_printlist(&items);
	counter = pf_countliststr(&items);
	pf_freelist(&items);
	return (counter);
}
