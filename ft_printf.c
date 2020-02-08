/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:06:07 by iwillens          #+#    #+#             */
/*   Updated: 2020/02/07 23:05:45 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

void pfgetvaarg_int(va_list ap, t_content *cnt)
{
	cnt->value = (void*)malloc(sizeof(long long int));
	if (cnt->length == 0 || cnt->length & (LM_CHAR | LM_SHORT))
		*(int*)(cnt->value) = va_arg(ap, int);
	else if (cnt->length == LM_LONG)
		*(long int*)(cnt->value) = va_arg(ap, long int);
	else if (cnt->length == LM_INTMAX)
		*(intmax_t*)(cnt->value) = va_arg(ap, intmax_t);
	else if (cnt->length == LM_SIZE_T)
		*(size_t*)(cnt->value) = va_arg(ap, size_t);
	else if (cnt->length == LM_PTRDIFF)
		*(ptrdiff_t*)(cnt->value) = va_arg(ap, ptrdiff_t);
}

void pfgetvaarg_uint(va_list ap, t_content *cnt)
{
	if (ft_strchr(PF_SPEC_LLONG, cnt->type))
			(cnt->length = LM_LONGLONG);
	cnt->value = (void*)malloc(sizeof(unsigned long long int));
	if (cnt->length == 0 || cnt->length & (LM_CHAR | LM_SHORT))
		*(int*)(cnt->value) = va_arg(ap, unsigned int);
	else if (cnt->length == LM_LONG)
		*(unsigned long int*)(cnt->value) = va_arg(ap, unsigned long int);
	else if (cnt->length == LM_LONGLONG)
		*(unsigned long int*)(cnt->value) = va_arg(ap, unsigned long long int);
	else if (cnt->length == LM_INTMAX)
		*(intmax_t*)(cnt->value) = va_arg(ap, uintmax_t);
	else if (cnt->length == LM_SIZE_T)
		*(size_t*)(cnt->value) = va_arg(ap, size_t);
	else if (cnt->length == LM_PTRDIFF)
		*(ptrdiff_t*)(cnt->value) = va_arg(ap, ptrdiff_t);
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
		if (cnt->type != '!')
			count += ft_strlen(cnt->printable_value);
		else
			count += ft_strlen(cnt->orig_content);

		(tmp) = (tmp)->next;
	}
	return (count);
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

int a;
a = 1;
while (a == 1)
{
	a = 1;
}



	return (counter);
/*
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
		long long *c;
	   	c = va_arg(ap, void*);
		ft_putnbr_fd((int)(*c), 1);
		i++;
	}
*/
		

	return 0;
}
