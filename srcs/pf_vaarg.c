/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_vaarg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 11:15:49 by iwillens          #+#    #+#             */
/*   Updated: 2024/05/29 17:31:30 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** now that we know the types we are dealing with, we can get the
** arguments from the va_list and store them in the content struct.
*/
void		get_values(va_list *ap, t_content *cnt)
{
	if (cnt->width.wc == PF_WC_AP)
		cnt->width.nb = va_arg(*ap, int);
	if (cnt->prec.wc == PF_WC_AP)
		cnt->prec.nb = va_arg(*ap, int);
	if (ft_strchr(PF_SPEC_INT, cnt->type))
		cnt->value.i = va_arg(*ap, int);
	else if (ft_strchr(PF_SPEC_PTR, cnt->type))
		cnt->value.u = (unsigned long long)va_arg(*ap, void *);
	else if (ft_strchr(PF_SPEC_UINT, cnt->type))
		cnt->value.u = va_arg(*ap, unsigned int);
	else if (ft_strchr(PF_SPEC_STR, cnt->type))
		cnt->value.s = pf_strchecknull((char*)va_arg(*ap, char*));
	else if (ft_strchr(PF_SPEC_CHAR, cnt->type))
	{
		cnt->value.i = (int)cnt->type;
		cnt->type = 'c';
	}
}
