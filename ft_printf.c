/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:06:07 by iwillens          #+#    #+#             */
/*   Updated: 2020/02/05 07:32:08 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

void pf_getvaarg(va_list ap, t_list **items)
{
	t_content *cnt;
	t_list *tmp;
	tmp = *items;
		while(tmp)
	{
		cnt = (t_content*)(tmp)->content;
		if (cnt->width.wildcard == 1)
			cnt->width.number = va_arg(ap, size_t);
		if (cnt->precision.wildcard == 1)
			cnt->precision.number = va_arg(ap, size_t);
		if (ft_strchr(PF_SPEC_LLONG, cnt->type))
		{
			cnt->value = (void*)malloc(sizeof(long long int));
			*(long long int*)(cnt->value) = va_arg(ap, long long int);

		}
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
		{
			cnt->value = (char*)va_arg(ap, char*);
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
		if (cnt->type != '!')
			ft_putstr_fd(cnt->printable_value, 1);
		else
			ft_putstr_fd(cnt->orig_content, 1);		

		(tmp) = (tmp)->next;
	}
}

int	ft_printf(const char *str, ...)
{
	va_list		ap;
	const char	*string;
	t_list		*items;
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
