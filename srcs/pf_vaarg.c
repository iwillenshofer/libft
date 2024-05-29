/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_vaarg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 11:15:49 by iwillens          #+#    #+#             */
/*   Updated: 2024/05/29 00:22:56 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	pfgetvaarg_int(va_list *ap, t_content *cnt)
{
	cnt->value = (void*)malloc(sizeof(long long int));
	if (!cnt->value)
		return ;
	*(int*)(cnt->value) = va_arg(*ap, int);
}

static void	pfgetvaarg_uint(va_list *ap, t_content *cnt)
{
	if (ft_strchr(PF_SPEC_LLONG, cnt->type))
		(cnt->length = LM_LONGLONG);
	cnt->value = (void*)malloc(sizeof(t_ulli));
	if (!cnt->value)
		return ;
	if (cnt->length == 0)
		*(int*)(cnt->value) = va_arg(*ap, unsigned int);
	else if (cnt->length == LM_LONGLONG)
		*(unsigned long int*)(cnt->value) = va_arg(*ap, t_ulli);
}

static void	pf_getvaarg_specialcases(va_list *ap, t_content *cnt)
{
	if (cnt->type == 's')
		cnt->value = pf_strchecknull((char*)va_arg(*ap, char*));
	else if (cnt->type == 'c')
	{
		cnt->value = (void*)malloc(sizeof(int));
		if (!cnt->value)
			return ;
		*(int*)(cnt->value) = (int)va_arg(*ap, int);
	}
}

void		pf_getvaarg(va_list *ap, t_list **items)
{
	t_content	*cnt;
	t_list		*tmp;

	tmp = *items;
	while (tmp)
	{
		cnt = (t_content*)(tmp)->content;
		if (cnt->width.wc == PF_WC_AP)
			cnt->width.nb = va_arg(*ap, int);
		if (cnt->prec.wc == PF_WC_AP)
			cnt->prec.nb = va_arg(*ap, int);
		if (ft_strchr(PF_SPEC_INT, cnt->type))
			pfgetvaarg_int(ap, cnt);
		else if (ft_strchr(PF_SPEC_UINT, cnt->type))
			pfgetvaarg_uint(ap, cnt);
		else
			pf_getvaarg_specialcases(ap, cnt);
		tmp = tmp->next;
	}
}
