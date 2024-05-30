/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_uint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:27:02 by iwillens          #+#    #+#             */
/*   Updated: 2024/05/30 10:46:57 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void set_padding_and_precision(t_content *cnt)
{
	cnt->prt.padding_char = ' ';
	if (cnt->prec.wc && cnt->prec.nb > cnt->prt.num_len)
		cnt->prt.precision_len = cnt->prec.nb - cnt->prt.num_len;
	if (cnt->width.wc && cnt->width.nb > cnt->prt.num_len + cnt->prt.precision_len)
		cnt->prt.padding_len = cnt->width.nb - (cnt->prt.num_len + cnt->prt.precision_len);
	if (cnt->prt.signal_char && cnt->prt.padding_len)
		cnt->prt.padding_len--;
	if (cnt->flags & PF_FLAG_ZERO && !(cnt->flags & PF_FLAG_MINUS) && !(cnt->prec.wc))
		cnt->prt.padding_char = '0';
}

/*
** number of digits is 0 if the precision is 0 and the value is 0
*/
#include <stdio.h>
static void set_number(t_content *cnt)
{
	cnt->prt.base = PF_BASE_10;
	if (cnt->type == 'x' || cnt->type == 'p')
		cnt->prt.base = PF_BASE_16;
	else if (cnt->type == 'X')
		cnt->prt.base = PF_BASE_16U;
	if ((!cnt->prec.wc || cnt->prec.nb || cnt->value.u))
		cnt->prt.num_len = ft_numlen_base(cnt->value.u, cnt->prt.base);

	/*printf("	size_t		num_len: %lu;\n\
	size_t		cnt->prec.wc: %lu;\n\
	size_t		cnt->prec.nb: %lu;\n\
	size_t		cnt->value.i: %llu;\n\
	", cnt->prt.num_len, cnt->prec.wc, cnt->prec.nb, cnt->value.u);
	*/
}

void	set_prepend_chars(t_content *cnt)
{
	if (cnt->type == 'p' || (cnt->type == 'x' && cnt->flags & PF_FLAG_SHARP && cnt->value.i)
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


void	process_uint(t_content *cnt)
{
	set_number(cnt);
	set_padding_and_precision(cnt);
	set_prepend_chars(cnt);
	if (!(cnt->flags & PF_FLAG_MINUS) && (!cnt->prt.prepend[0] || cnt->prt.padding_char == ' '))
		printnchar(cnt->prt.padding_char, cnt->prt.padding_len, cnt);
	if (cnt->flags & PF_FLAG_PLUS && cnt->value.i >= 0)
		printchar('+', cnt);
	printstr(cnt->prt.prepend, cnt);
	if (!(cnt->flags & PF_FLAG_MINUS) && (cnt->prt.prepend[0] && cnt->prt.padding_char == '0'))
		printnchar(cnt->prt.padding_char, cnt->prt.padding_len, cnt);
	printnchar('0', cnt->prt.precision_len, cnt);
	if ((!cnt->prec.wc || cnt->prec.nb || cnt->value.i))
		printnumber(cnt->value.i, cnt->prt.base, cnt);
	if ((cnt->flags & PF_FLAG_MINUS))
		printnchar(cnt->prt.padding_char, cnt->prt.padding_len, cnt);
	/*
	printf("	size_t		num_len: %lu;\n\
	size_t		padding_len: %lu;\n\
	size_t		precision_len: %lu;\n\
	char		padding_char: '%c';\n\
	char		signal_char: '%c';\n\
	int			sign: %d;\n", cnt->prt.num_len, cnt->prt.padding_len, cnt->prt.precision_len, cnt->prt.padding_char, cnt->prt.signal_char, cnt->prt.sign);
	*/
}
