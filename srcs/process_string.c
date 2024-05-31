/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:48:53 by iwillens          #+#    #+#             */
/*   Updated: 2024/05/31 09:40:41 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	process_char(t_printf *printf)
{
	t_content	*cnt;

	cnt = &printf->cnt;
	cnt->prt.padding_char = ' ';
	if (cnt->flags & PF_FLAG_ZERO && !(cnt->flags & PF_FLAG_MINUS))
		cnt->prt.padding_char = '0';
	if (cnt->width.nb > 1)
		cnt->prt.padding_len = cnt->width.nb - 1;
	if (!(cnt->flags & PF_FLAG_MINUS))
		storenchar(cnt->prt.padding_char, cnt->prt.padding_len, printf);
	storechar(cnt->value.i, printf);
	if ((cnt->flags & PF_FLAG_MINUS))
		storenchar(cnt->prt.padding_char, cnt->prt.padding_len, printf);
}

void	process_string(t_printf *printf)
{
	char		*tmp;
	t_content	*cnt;

	cnt = &printf->cnt;
	tmp = cnt->value.s;
	cnt->prt.padding_char = ' ';
	while (*tmp && (!(cnt->prec.wc) || (cnt->prt.num_len < cnt->prec.nb)))
	{
		cnt->prt.num_len++;
		tmp++;
	}
	if (cnt->flags & PF_FLAG_ZERO && cnt->flags & PF_FLAG_MINUS)
		cnt->prt.padding_char = '0';
	if (cnt->width.nb > cnt->prt.num_len)
		cnt->prt.padding_len = cnt->width.nb - cnt->prt.num_len;
	if (!(cnt->flags & PF_FLAG_MINUS))
		storenchar(cnt->prt.padding_char, cnt->prt.padding_len, printf);
	storenstr(cnt->value.s, cnt->prt.num_len, printf);
	if ((cnt->flags & PF_FLAG_MINUS))
		storenchar(cnt->prt.padding_char, cnt->prt.padding_len, printf);
}
