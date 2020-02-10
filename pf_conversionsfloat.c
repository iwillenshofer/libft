/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_conversionsfloat.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 10:15:37 by iwillens          #+#    #+#             */
/*   Updated: 2020/02/10 14:23:09 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		pf_convert_float(t_content *cnt)
{
	if (cnt->prec.nb > 0)
		cnt->prt_v =
			ft_ftoa_base(*(double*)(cnt->value), cnt->prec.nb);
	else if (cnt->prec.wc == PF_WC_SET)
		cnt->prt_v =
			ft_ftoa_base(*(double*)(cnt->value), 0);
	else
		cnt->prt_v =
			ft_ftoa_base(*(double*)(cnt->value), 6);
}

/*
** this function sets printable value (prt_v) as
** the result of ftoa_base.
*/

static void	pf_convert_mantissa_itoa(t_content *cnt, long double n_dbl)
{
	if (cnt->prec.nb > 0)
		cnt->prt_v =
			ft_ftoa_base(n_dbl, cnt->prec.nb);
	else if (cnt->prec.wc == PF_WC_SET)
		cnt->prt_v =
			ft_ftoa_base(n_dbl, 0);
	else
		cnt->prt_v =
			ft_ftoa_base(n_dbl, 6);
	cnt->prt_v = ft_insertchr_end(cnt->prt_v, 'e');
	cnt->prt_v = ft_insertchr_end(cnt->prt_v, '+');
}

void		pf_convert_mantissa(t_content *cnt)
{
	long double	n_dbl;
	size_t		counter;
	char		*str1;
	char		*str2;

	counter = 0;
	n_dbl = *(double*)(cnt->value);
	while ((t_lli)n_dbl >= 10 || (t_lli)n_dbl <= -10)
	{
		n_dbl = n_dbl / 10.0;
		counter++;
	}
	pf_convert_mantissa_itoa(cnt, n_dbl);
	str1 = cnt->prt_v;
	str2 = ft_itoa(counter);
	if (counter < 10)
		str2 = ft_insertchr_start(str2, '0');
	cnt->prt_v = ft_strjoin(str1, str2);
	if (str1)
		free(str1);
	if (str2)
		free(str2);
}

/*
** this function sets printable value (prt_v) as
** float or mantissa, whichever is the shortest.
*/

void		pf_convert_shortest_floatmant(t_content *cnt)
{
	t_content *tmpcont;

	tmpcont = (t_content*)malloc(sizeof(t_content));
	pf_fillblank(&tmpcont);
	tmpcont->prec.nb = cnt->prec.nb;
	tmpcont->prec.wc = cnt->prec.wc;
	tmpcont->value = cnt->value;
	pf_convert_float(tmpcont);
	if (ft_strlen(tmpcont->prt_v) < ft_strlen(cnt->prt_v))
	{
		if (cnt->prt_v)
			free(cnt->prt_v);
		cnt->prt_v = tmpcont->prt_v;
	}
	else
	{
		if (tmpcont->prt_v)
			free(tmpcont->prt_v);
	}
	if (tmpcont)
		free(tmpcont);
}
