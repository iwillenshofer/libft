/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:27:02 by iwillens          #+#    #+#             */
/*   Updated: 2024/05/31 09:35:41 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	set_signal(t_content *cnt)
{
	if (cnt->value.i < 0)
	{
		cnt->value.i = -cnt->value.i;
		cnt->prt.sign = 1;
		cnt->prt.signal_char = '-';
	}
	else if (cnt->flags & PF_FLAG_PLUS)
		cnt->prt.signal_char = '+';
	else if (cnt->flags & PF_FLAG_SPACE)
		cnt->prt.signal_char = ' ';
}

static void	set_padding_and_precision(t_content *cnt)
{
	cnt->prt.padding_char = ' ';
	if (cnt->prec.wc && cnt->prec.nb > cnt->prt.num_len)
		cnt->prt.precision_len = cnt->prec.nb - cnt->prt.num_len;
	if (cnt->width.wc && cnt->width.nb > cnt->prt.num_len
		+ cnt->prt.precision_len)
		cnt->prt.padding_len = cnt->width.nb
			- (cnt->prt.num_len + cnt->prt.precision_len);
	if (cnt->prt.signal_char && cnt->prt.padding_len)
		cnt->prt.padding_len--;
	if (cnt->flags & PF_FLAG_ZERO
		&& !(cnt->flags & PF_FLAG_MINUS) && (!cnt->prec.wc))
		cnt->prt.padding_char = '0';
}

/*
** number of digits is 0 if the precision is 0 and the value is 0
*/
static void	set_number(t_content *cnt)
{
	if ((!cnt->prec.wc || cnt->prec.nb || cnt->value.i))
		cnt->prt.num_len = ft_numlen_base(cnt->value.i, PF_BASE_10);
}

void	process_int(t_printf *printf)
{
	t_content	*cnt;

	cnt = &printf->cnt;
	set_signal(cnt);
	set_number(cnt);
	set_padding_and_precision(cnt);
	if (cnt->prt.padding_len && cnt->prt.padding_char == '0'
		&& cnt->prt.signal_char)
		storechar(cnt->prt.signal_char, printf);
	if (!(cnt->flags & PF_FLAG_MINUS))
		storenchar(cnt->prt.padding_char, cnt->prt.padding_len, printf);
	if ((!cnt->prt.padding_len || cnt->prt.padding_char == ' ')
		&& cnt->prt.signal_char)
		storechar(cnt->prt.signal_char, printf);
	storenchar('0', cnt->prt.precision_len, printf);
	if ((!cnt->prec.wc || cnt->prec.nb || cnt->value.i))
		storenumber(cnt->value.i, PF_BASE_10, printf);
	if (cnt->flags & PF_FLAG_MINUS)
		storenchar(cnt->prt.padding_char, cnt->prt.padding_len, printf);
}
