/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_uint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:27:02 by iwillens          #+#    #+#             */
/*   Updated: 2024/05/31 09:38:12 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	set_padding_and_precision(t_content *cnt)
{
	cnt->prt.padding_char = ' ';
	if (cnt->prec.wc && cnt->prec.nb > cnt->prt.num_len)
		cnt->prt.precision_len = cnt->prec.nb - cnt->prt.num_len;
	if (cnt->width.wc && cnt->width.nb
		> cnt->prt.num_len + cnt->prt.precision_len)
		cnt->prt.padding_len = cnt->width.nb
			- (cnt->prt.num_len + cnt->prt.precision_len);
	if (cnt->prt.signal_char && cnt->prt.padding_len)
		cnt->prt.padding_len--;
	if (cnt->flags & PF_FLAG_ZERO
		&& !(cnt->flags & PF_FLAG_MINUS) && !(cnt->prec.wc))
		cnt->prt.padding_char = '0';
}

/*
** number of digits is 0 if the precision is 0 and the value is 0
*/
static void	set_number(t_content *cnt)
{
	cnt->prt.base = PF_BASE_10;
	if (cnt->type == 'x' || cnt->type == 'p')
		cnt->prt.base = PF_BASE_16;
	else if (cnt->type == 'X')
		cnt->prt.base = PF_BASE_16U;
	if ((!cnt->prec.wc || cnt->prec.nb || cnt->value.u))
		cnt->prt.num_len = ft_numlen_base(cnt->value.u, cnt->prt.base);
}

static void	set_prepend_chars(t_content *cnt)
{
	if (cnt->type == 'p'
		|| (cnt->type == 'x' && cnt->flags & PF_FLAG_SHARP && cnt->value.i)
		|| (cnt->type == 'X' && cnt->flags & PF_FLAG_SHARP && cnt->value.i))
	{
		if (cnt->prt.padding_len > 2)
			cnt->prt.padding_len -= 2;
		else
			cnt->prt.padding_len = 0;
		cnt->prt.prepend[0] = '0';
		cnt->prt.prepend[1] = 'x';
		if (cnt->type == 'X')
			cnt->prt.prepend[1] = 'X';
	}
}

void	process_uint(t_printf *printf)
{
	t_content	*cnt;

	cnt = &printf->cnt;
	set_number(cnt);
	set_padding_and_precision(cnt);
	set_prepend_chars(cnt);
	if (!(cnt->flags & PF_FLAG_MINUS)
		&& (!cnt->prt.prepend[0] || cnt->prt.padding_char == ' '))
		storenchar(cnt->prt.padding_char, cnt->prt.padding_len, printf);
	if (cnt->flags & PF_FLAG_PLUS && cnt->value.i >= 0)
		storechar('+', printf);
	storestr(cnt->prt.prepend, printf);
	if (!(cnt->flags & PF_FLAG_MINUS)
		&& (cnt->prt.prepend[0] && cnt->prt.padding_char == '0'))
		storenchar(cnt->prt.padding_char, cnt->prt.padding_len, printf);
	storenchar('0', cnt->prt.precision_len, printf);
	if ((!cnt->prec.wc || cnt->prec.nb || cnt->value.i))
		storenumber(cnt->value.i, cnt->prt.base, printf);
	if ((cnt->flags & PF_FLAG_MINUS))
		storenchar(cnt->prt.padding_char, cnt->prt.padding_len, printf);
}
