/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_conversions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 17:40:23 by iwillens          #+#    #+#             */
/*   Updated: 2020/02/10 14:24:29 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	pf_convert_string(t_content *cnt)
{
	size_t strlen;

	strlen = ft_strlen(cnt->value);
	if ((cnt->prec.wc == (PF_WC_SET) || cnt->prec.wc == (PF_WC_AP)) &&
		cnt->prec.nb < (int)strlen && cnt->prec.nb >= 0)
	{
		cnt->prt_v = ft_strndup((char*)(cnt->value), cnt->prec.nb);
	}
	else
		cnt->prt_v = ft_strndup((char*)(cnt->value), strlen);
}

static void	pf_convert_content_number(t_content *cnt)
{
	if (cnt->type == 'i' || cnt->type == 'd')
		pf_convert_integer(cnt, T_SIGNED, 10);
	if (cnt->type == 'u')
		pf_convert_uinteger(cnt, T_UNSIGNED, 10);
	if (cnt->type == 'p')
		cnt->flags = cnt->flags | PF_FLAG_SHARP;
	if (cnt->type == 'o')
		pf_convert_uinteger(cnt, T_UNSIGNED, 8);
	if (cnt->type == 'x' || cnt->type == 'X' || cnt->type == 'p')
		pf_convert_uinteger(cnt, T_UNSIGNED, 16);
	if ((cnt->type == 'f' || cnt->type == 'F'))
		pf_convert_float(cnt);
	if (cnt->type == 'e' || cnt->type == 'E' || cnt->type == 'g' ||
	cnt->type == 'G')
		pf_convert_mantissa(cnt);
	if (cnt->type == 'g' || cnt->type == 'G')
		pf_convert_shortest_floatmant(cnt);
}

void		pf_convert_content(t_content *cnt)
{
	pf_convert_content_number(cnt);
	if (cnt->type == 's')
		pf_convert_string(cnt);
	if (cnt->type == 'c')
		cnt->prt_v = ft_chr_unicode(*(wchar_t*)(cnt->value), 1);
	if (cnt->type == '%')
		cnt->prt_v = strdup("%");
	if (cnt->type == 'n')
	{
		cnt->prt_v = strdup("");
		return ;
	}
	if (cnt->type == 'X' || cnt->type == 'F' || cnt->type == 'G')
		ft_strtoupper(cnt->prt_v);
	pf_flags_add(cnt);
}

void		pf_convertlist(t_list **lst)
{
	t_list *tmp;

	tmp = *lst;
	while (tmp)
	{
		pf_convert_content((tmp)->content);
		(tmp) = tmp->next;
	}
}
