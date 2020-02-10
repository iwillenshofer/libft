/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_vaarg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 11:15:49 by iwillens          #+#    #+#             */
/*   Updated: 2020/02/10 11:18:39 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void pfgetvaarg_nptr(va_list ap, t_content *cnt)
{
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

static void pfgetvaarg_int(va_list ap, t_content *cnt)
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
}

static void pfgetvaarg_uint(va_list ap, t_content *cnt)
{
	if (ft_strchr(PF_SPEC_LLONG, cnt->type))
			(cnt->length = LM_LONGLONG);
	cnt->value = (void*)malloc(sizeof(t_ulli));
	if (cnt->length == 0 )
		*(int*)(cnt->value) = va_arg(ap, unsigned int);
	else if (cnt->length == LM_SHORT)
		*(unsigned short*)(cnt->value) =
			(unsigned short)va_arg(ap, unsigned int);
	else if (cnt->length == LM_CHAR)
		*(unsigned char*)(cnt->value) =
			(unsigned char)va_arg(ap, unsigned int);
	else if (cnt->length == LM_LONG)
		*(unsigned long int*)(cnt->value) = va_arg(ap, unsigned long int);
	else if (cnt->length == LM_LONGLONG || cnt->length == LM_LONGDBL)
		*(unsigned long int*)(cnt->value) = va_arg(ap, t_ulli);
	else if (cnt->length == LM_INTMAX)
		*(intmax_t*)(cnt->value) = va_arg(ap, uintmax_t);
	else if (cnt->length == LM_SIZE_T)
		*(size_t*)(cnt->value) = va_arg(ap, size_t);
	else if (cnt->length == LM_PTRDIFF)
		*(ptrdiff_t*)(cnt->value) = va_arg(ap, ptrdiff_t);
}

static void pf_getvaarg_specialcases(va_list ap, t_content *cnt)
{
	if (ft_strchr(PF_SPEC_DOUBLE, cnt->type) && cnt->length & LM_LONGDBL)
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
}

void pf_getvaarg(va_list ap, t_list **items)
{
	t_content *cnt;
	t_list *tmp;

	tmp = *items;
		while(tmp)
	{
		cnt = (t_content*)(tmp)->content;
		if (cnt->width.wc == PF_WC_AP)
			cnt->width.nb = va_arg(ap, int);
		if (cnt->prec.wc == PF_WC_AP)
			cnt->prec.nb =va_arg(ap, int);
		if (ft_strchr(PF_SPEC_INT, cnt->type))
			pfgetvaarg_int(ap, cnt);
		else if (ft_strchr(PF_SPEC_UINT, cnt->type))
			pfgetvaarg_uint(ap, cnt);
		else if (ft_strchr(PF_SPEC_NPOINTER, cnt->type))
			pfgetvaarg_nptr(ap, cnt);
		else
			pf_getvaarg_specialcases(ap, cnt);
		tmp = tmp->next;
	}
}