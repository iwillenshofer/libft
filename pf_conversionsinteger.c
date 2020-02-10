/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_conversionsinteger.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 10:11:29 by iwillens          #+#    #+#             */
/*   Updated: 2020/02/10 10:14:55 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void pf_convert_integer_itoa(t_content *cnt, short type, size_t base)
{
	if (cnt->length == 0)
		cnt->prt_v = 
		ft_itoa_base((int)(*(int*)(cnt->value) &M_I), base, type);
	else if (cnt->length == LM_CHAR)
		cnt->prt_v = 
		ft_itoa_base((t_lli)(*(t_lli*)(cnt->value) & M_CHR), base, type);
	else if (cnt->length == LM_SHORT)
		cnt->prt_v =
		ft_itoa_base((t_lli)(*(t_lli*)(cnt->value) & M_SHRT), base, type);
	else if (cnt->length == LM_LONG)
		cnt->prt_v =
		ft_itoa_base((t_lli)(*(t_lli*)(cnt->value) & M_LLI), base, type);
	else if (cnt->length == LM_LONGLONG || cnt->length == LM_LONGDBL)
		cnt->prt_v =
		ft_itoa_base((t_lli)(*(t_lli*)(cnt->value) & M_LLI), base, type);
	else if (cnt->length == LM_INTMAX)
		cnt->prt_v =
		ft_itoa_base((t_lli)(*(uintmax_t*)(cnt->value) & M_I), base, type);
	else if (cnt->length == LM_SIZE_T)
		cnt->prt_v =
		ft_itoa_base((t_lli)(*(size_t*)(cnt->value) & M_LLI), base, type);
	else if (cnt->length == LM_PTRDIFF)
		cnt->prt_v =
		ft_itoa_base((t_lli)(*(ptrdiff_t*)(cnt->value) & M_LLI), base, type);
}

void pf_convert_integer(t_content *cnt, short type, size_t base)
{
	if (ft_strchr(PF_SPEC_INT, cnt->type))
			pf_convert_integer_itoa(cnt, type, base);
	else
		cnt->prt_v = ft_itoa_base(*(t_lli*)(cnt->value), base, type);
	if (cnt->prec.nb > 0)
		cnt->prt_v = ft_fillnchr_start(cnt->prt_v, '0',
			cnt->prec.nb);
	else if (cnt->prec.nb == 0 &&
	(cnt->prec.wc == PF_WC_SET || (cnt->prec.wc == PF_WC_AP)) &&
	ft_strncmp(cnt->prt_v, "0",	ft_strlen(cnt->prt_v)) == 0)
		cnt->prt_v[0] = '\0';
}

static void pf_convert_integer_uitoa(t_content *cnt, short type, size_t base)
{
	if (cnt->length == 0)
		cnt->prt_v =
		ft_itoa_base(*(unsigned int*)(cnt->value) &  M_UI, base, type);
	else if (cnt->length == LM_CHAR)
		cnt->prt_v =
		ft_itoa_base(*(t_ulli*)(cnt->value) & M_UCHR , base, type);
	else if (cnt->length == LM_SHORT)
		cnt->prt_v =
		ft_itoa_base(*(t_ulli*)(cnt->value) & M_USHRT, base, type);
	else if (cnt->length == LM_LONG)
		cnt->prt_v =
		ft_itoa_base(*(t_ulli*)(cnt->value)  & M_ULLI, base, type);
	else if (cnt->length == LM_LONGLONG || cnt->length == LM_LONGDBL)
		cnt->prt_v =
		ft_itoa_base(*(t_ulli*)(cnt->value) & M_ULLI, base, type);
	else if (cnt->length == LM_INTMAX)
		cnt->prt_v =
		ft_itoa_base(*(uintmax_t*)(cnt->value) & M_UI, base, type);
	else if (cnt->length == LM_SIZE_T)
		cnt->prt_v =
		ft_itoa_base(*(size_t*)(cnt->value) & M_ULLI, base, type);
	else if (cnt->length == LM_PTRDIFF)
		cnt->prt_v =
		ft_itoa_base(*(ptrdiff_t*)(cnt->value) &  M_ULLI, base, type);
}

void pf_convert_uinteger(t_content *cnt, short type, size_t base)
{
	if ( ft_strchr(PF_SPEC_UINT, cnt->type))
		pf_convert_integer_uitoa(cnt, type, base);
	else
		cnt->prt_v = ft_itoa_base(*(t_ulli*)(cnt->value), base, type);
	if (cnt->prec.nb > 0)
		cnt->prt_v = ft_fillnchr_start(cnt->prt_v, '0',
			cnt->prec.nb);
	else if (cnt->prec.nb == 0 &&
		(cnt->prec.wc == PF_WC_SET || (cnt->prec.wc == PF_WC_AP)) &&
			ft_strncmp(cnt->prt_v, "0", ft_strlen(cnt->prt_v)) == 0)
		cnt->prt_v[0] = '\0';
}