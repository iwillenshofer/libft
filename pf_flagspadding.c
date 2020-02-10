/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_flagspadding.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 10:04:39 by iwillens          #+#    #+#             */
/*   Updated: 2020/02/10 10:05:05 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	pf_flags_padding_specialcases(t_content *cnt, size_t str_len)
{
	if ((int)cnt->width.nb < 0)
	{
		cnt->width.nb = ft_negative_topositive((int)cnt->width.nb);
		cnt->flags = cnt->flags | PF_FLAG_MINUS;
		cnt->width.was_negative = 1;
	}
	else if (str_len > 0 && (cnt->flags & PF_FLAG_ZERO ))
	{
		if (((!(cnt->flags & PF_FLAG_MINUS) || cnt->width.was_negative) &&
		cnt->pad_chr == '0' && cnt->width.nb > 0 && cnt->prt_v[0] == '-') ||
		(cnt->flags & PF_FLAG_MINUS && cnt->prec.wc == PF_WC_DEFAULT &&
		(cnt->width.was_negative) && cnt->prt_v[0] != '-'))
			cnt->width.nb -= 1;
	}		
}

void	pf_flags_padding(t_content *cnt)
{	
	size_t str_len;
	size_t width;

	str_len = ft_strlen(cnt->prt_v);
	pf_flags_padding_specialcases(cnt, str_len);
	width = cnt->width.nb;
	if (cnt->pad_chr == '0' && !(cnt->flags & PF_FLAG_MINUS))
		cnt->prt_v = ft_fillnchr_start(cnt->prt_v, cnt->pad_chr, width);
	else
	{
		if(cnt->flags & (PF_FLAG_MINUS) && (cnt->flags & (PF_FLAG_ZERO)) &&
		cnt->prec.wc == PF_WC_AP)
			width--;
		while (str_len < width)
		{
			if (cnt->flags & PF_FLAG_MINUS)
				cnt->prt_v = ft_insertchr_end(cnt->prt_v, ' ');
			else
				cnt->prt_v = ft_insertchr_start(cnt->prt_v, cnt->pad_chr);
			width--;
		}
	}
}