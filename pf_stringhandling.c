/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_stringhandling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 04:39:03 by iwillens          #+#    #+#             */
/*   Updated: 2020/02/10 07:42:25 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void pf_writecharstr(char *s)
{
	int i;
	char c;
	i = 0;

	while (s && s[i] != '\0')
	{
		c = s[i];
		if (c == '*')
			c = 0;
		ft_putchar_fd(c, 1);
		i++;
	}
}


void pf_set_npointervalue(t_content *cnt, size_t count)
{
	if (cnt->length == 0)
		*(int*)(cnt->value) = (int)(count);
	else if (cnt->length == LM_LONG)
		*(long int*)cnt->value = (long int)count;
	else if (cnt->length == LM_LONGLONG || cnt->length == LM_LONGDBL)
		*(long long int*)cnt->value = (long long int)count;
	else if (cnt->length == LM_INTMAX)
		*(intmax_t*)(cnt->value) = (intmax_t)count;
	else if (cnt->length == LM_SIZE_T)
		*(size_t*)(cnt->value) = (size_t)count;
	else if (cnt->length == LM_PTRDIFF)
		*(ptrdiff_t*)(cnt->value) = (ptrdiff_t)count;
	else if (cnt->length == LM_SHORT)
		*(short*)(cnt->value) = (short)count;
	else if (cnt->length == LM_CHAR)
		*(char*)(cnt->value) = (char)(count);
}

/*
** conta a quantidade de caracteres em toda a lista
** para dar o retorno do printf.
*/

size_t pf_countliststr(t_list **lst)
{
	t_content	*cnt;
	t_list		*tmp;
	size_t		count;

	count = 0;
	tmp = *lst;
	while (tmp)
	{
		cnt = (tmp)->content;
		if (cnt->type == 'n' && cnt->value != NULL)
			pf_set_npointervalue(cnt, count);
		else if (cnt->type != '!')
			count += ft_strlen(cnt->prt_v);
		else
			count += ft_strlen(cnt->orig_content);

		(tmp) = (tmp)->next;
	}
	return (count);
}

char *pf_strchecknull(char *str)
{
	if (!str)
		return ("(null)");
	else
		return (str);
}