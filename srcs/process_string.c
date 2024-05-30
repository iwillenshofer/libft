/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:48:53 by iwillens          #+#    #+#             */
/*   Updated: 2024/05/30 11:50:16 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void process_char(t_content *cnt)
{
    char padding_char;
    int padding;

    padding_char = ' ';
    padding = 0;
    if (cnt->flags & PF_FLAG_ZERO && !(cnt->flags & PF_FLAG_MINUS))
        padding_char = '0';
    if (cnt->width.nb > 1)
        padding = cnt->width.nb - 1;
    if (!(cnt->flags & PF_FLAG_MINUS))
        printnchar(padding_char, padding, cnt);
    printchar(cnt->value.i, cnt);
    if ((cnt->flags & PF_FLAG_MINUS))
        printnchar(padding_char, padding, cnt);
}

/*
** printing functions
*/
void	process_string(t_content *cnt)
{
	char padding_char;
	size_t padding;
	size_t	len;
	char *tmp;

	tmp = cnt->value.s;
	len = 0;
	padding = 0;
	padding_char = ' ';
	while (*tmp && (!(cnt->prec.wc) || (len < cnt->prec.nb)))
	{
		len++;
		tmp++;
	}
	if (cnt->flags & PF_FLAG_ZERO && cnt->flags & PF_FLAG_MINUS)
		padding_char = '0';

	if (cnt->width.nb > len)
		padding = cnt->width.nb - len;
	if (!(cnt->flags & PF_FLAG_MINUS))
		printnchar(padding_char, padding, cnt);
	printnstr(cnt->value.s, len, cnt);
	if ((cnt->flags & PF_FLAG_MINUS))
		printnchar(padding_char, padding, cnt);
}
