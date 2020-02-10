/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_flagsapply.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 21:43:22 by iwillens          #+#    #+#             */
/*   Updated: 2020/02/10 10:42:10 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_flags_add_sharp(t_content *cnt)
{
	if (cnt->type == 'o')
		cnt->prt_v = ft_insertchr_start(cnt->prt_v, '0');
	else if (cnt->type == 'x' || cnt->type == 'p')
	{
		cnt->prt_v = ft_insertchr_start(cnt->prt_v, 'x');
		cnt->prt_v = ft_insertchr_start(cnt->prt_v, '0');
	}
	else if (cnt->type == 'X')
	{
		cnt->prt_v = ft_insertchr_start(cnt->prt_v, 'X');
		cnt->prt_v = ft_insertchr_start(cnt->prt_v, '0');
	}
}

void	pf_flags_add_plus(t_content *cnt)
{
	if (cnt->prt_v[0] != '-')
		cnt->prt_v = ft_insertchr_start(cnt->prt_v, '+');
}

void	pf_flags_add_space(t_content *cnt)
{
	if (cnt->prt_v[0] != '-' &&
		cnt->prt_v[0] != '+')
		cnt->prt_v = ft_insertchr_start(cnt->prt_v, ' ');
}

void pf_flags_add(t_content *cnt)
{
	if (cnt->width.nb < 0)
	{
		cnt->flags = cnt->flags | PF_FLAG_MINUS;
		cnt->width.nb = ft_negative_topositive(cnt->width.nb);
		cnt->width.was_negative = 1;
		if (cnt->flags & PF_FLAG_ZERO)
			cnt->width.nb += 1;
	}
	if (cnt->flags & PF_FLAG_SHARP)
		pf_flags_add_sharp(cnt);
	if (cnt->flags & PF_FLAG_PLUS)
		pf_flags_add_plus(cnt);
	if (cnt->flags & PF_FLAG_SPACE)
		pf_flags_add_space(cnt);
	if (cnt->width.nb > 0)
	{
		if (cnt->flags & PF_FLAG_ZERO && (!(cnt->prec.wc != PF_WC_DEFAULT)
		|| cnt->prec.nb < 0))
			cnt->pad_chr = '0';
		else
			cnt->pad_chr = ' ';
		pf_flags_padding(cnt);
	}
}