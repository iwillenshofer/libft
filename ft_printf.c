/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:06:07 by iwillens          #+#    #+#             */
/*   Updated: 2020/02/08 20:51:30 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

void pfgetvaarg_nptr(va_list ap, t_content *cnt)
{
//	cnt->value = (void*)malloc(sizeof(long long int));
	if (cnt->length == 0)
		(cnt->value) = (va_arg(ap, int*));
	else if (cnt->length == LM_LONG)
		(cnt->value) = (va_arg(ap, long int*));
	else if (cnt->length == LM_LONGLONG || cnt->length == LM_LONGDBL)
		(cnt->value) = (va_arg(ap, long long int*));
	else if (cnt->length == LM_INTMAX)
		(cnt->value) = (va_arg(ap, intmax_t*));
	else if (cnt->length == LM_SIZE_T)
		(cnt->value) = (va_arg(ap, size_t*));
	else if (cnt->length == LM_PTRDIFF)
		(cnt->value) = (va_arg(ap, ptrdiff_t*));
	else if (cnt->length == LM_SHORT)
		(cnt->value) = (va_arg(ap, short*));
	else if (cnt->length == LM_CHAR)
		(cnt->value) = (va_arg(ap, char*));
}

void pfgetvaarg_int(va_list ap, t_content *cnt)
{
	cnt->value = (void*)malloc(sizeof(long long int));
	if (cnt->length == 0)
		*(int*)(cnt->value) = va_arg(ap, int);
	else if (cnt->length == LM_SHORT)
		*(short*)(cnt->value) = (short)va_arg(ap, int);
	else if (cnt->length == LM_CHAR)
		*(char*)(cnt->value) = (char)va_arg(ap, int);
	else if (cnt->length == LM_LONG)
		*(long int*)(cnt->value) = va_arg(ap, long int);
	else if (cnt->length == LM_LONGLONG || cnt->length == LM_LONGDBL)
		*(long long int*)(cnt->value) = va_arg(ap, long long int);
	else if (cnt->length == LM_INTMAX)
		*(intmax_t*)(cnt->value) = va_arg(ap, intmax_t);
	else if (cnt->length == LM_SIZE_T)
		*(size_t*)(cnt->value) = va_arg(ap, size_t);
	else if (cnt->length == LM_PTRDIFF)
		*(ptrdiff_t*)(cnt->value) = va_arg(ap, ptrdiff_t);
//	if (cnt->length == LM_SHORT)
//		*(short*)(cnt->value) = (short*)(cnt->value);
//	if (cnt->length == LM_CHAR)
//		*(int*)(cnt->value) = (char)*(int*)(cnt->value); 
}

void pfgetvaarg_uint(va_list ap, t_content *cnt)
{
	if (ft_strchr(PF_SPEC_LLONG, cnt->type))
			(cnt->length = LM_LONGLONG);
	cnt->value = (void*)malloc(sizeof(unsigned long long int));
	if (cnt->length == 0 )
		*(int*)(cnt->value) = va_arg(ap, unsigned int);
	else if (cnt->length == LM_SHORT)
		*(unsigned short*)(cnt->value) = (unsigned short)va_arg(ap, unsigned int);
	else if (cnt->length == LM_CHAR)
		*(unsigned char*)(cnt->value) = (unsigned char)va_arg(ap, unsigned int);
	else if (cnt->length == LM_LONG)
		*(unsigned long int*)(cnt->value) = va_arg(ap, unsigned long int);
	else if (cnt->length == LM_LONGLONG || cnt->length == LM_LONGDBL)
		*(unsigned long int*)(cnt->value) = va_arg(ap, unsigned long long int);
	else if (cnt->length == LM_INTMAX)
		*(intmax_t*)(cnt->value) = va_arg(ap, uintmax_t);
	else if (cnt->length == LM_SIZE_T)
		*(size_t*)(cnt->value) = va_arg(ap, size_t);
	else if (cnt->length == LM_PTRDIFF)
		*(ptrdiff_t*)(cnt->value) = va_arg(ap, ptrdiff_t);
	if (cnt->length == LM_SHORT)
		*(int*)(cnt->value) = (unsigned short)*(int*)(cnt->value);
	if (cnt->length == LM_CHAR)
		*(int*)(cnt->value) = (unsigned char)*(int*)(cnt->value);
}


void pf_getvaarg(va_list ap, t_list **items)
{
	t_content *cnt;
	t_list *tmp;
	tmp = *items;
		while(tmp)
	{
		cnt = (t_content*)(tmp)->content;
		if (cnt->width.wildcard == 1)
			cnt->width.number = va_arg(ap, int);
		if (cnt->precision.wildcard == 1)
			cnt->precision.number =va_arg(ap, int);
		if (ft_strchr(PF_SPEC_INT, cnt->type))
			pfgetvaarg_int(ap, cnt);
		else if (ft_strchr(PF_SPEC_UINT, cnt->type))
			pfgetvaarg_uint(ap, cnt);
		else if (ft_strchr(PF_SPEC_NPOINTER, cnt->type))
			pfgetvaarg_nptr(ap, cnt);
		else if (ft_strchr(PF_SPEC_DOUBLE, cnt->type) && cnt->length & LM_LONGDBL)
		{
			cnt->value = (void*)malloc(sizeof(long double));
			*(long double*)(cnt->value) = (long double)va_arg(ap, long double);
		}
		else if (ft_strchr(PF_SPEC_DOUBLE, cnt->type))
		{
			cnt->value = (void*)malloc(sizeof(double));
			*(double*)(cnt->value) = (double)va_arg(ap, double);
		}
		else if (cnt->type == 's')
			cnt->value = pf_strchecknull((char*)va_arg(ap, char*));
		else if (cnt->type == 'c')
		{
			cnt->value = (void*)malloc(sizeof(wchar_t));
			*(wchar_t*)(cnt->value) = (wchar_t)va_arg(ap, wchar_t);
		}
		tmp = tmp->next;
	}
}

void pf_printlist(t_list **lst)
{
	t_content *cnt;
	t_list *tmp;

	tmp = *lst;
	while (tmp)
	{
		cnt = (tmp)->content;
			if (cnt->type == '!')
				ft_putstr_fd(cnt->orig_content, 1);	
			else if (cnt->type == 'c' && *(wchar_t*)cnt->value == 0)
				pf_writecharstr(cnt->printable_value);
			else
				ft_putstr_fd(cnt->printable_value, 1);
					

		(tmp) = (tmp)->next;
	}
}


int	ft_printf(const char *str, ...)
{
	va_list		ap;
	const char	*string;
	t_list		*items;
	size_t		counter;

	items = NULL;

	string = str;
	
	int i;
	i = 0;
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
