/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_conversions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 17:40:23 by iwillens          #+#    #+#             */
/*   Updated: 2024/05/29 00:00:50 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	pf_convert_string(t_content *cnt)
{
	size_t strlen;

	strlen = ft_strlen(cnt->value);
	if ((cnt->prec.wc == (PF_WC_SET) || cnt->prec.wc == (PF_WC_AP)) &&
		cnt->prec.nb < (int)strlen && cnt->prec.nb >= 0)
	{
		cnt->prt_v = ft_strndup((char*)(cnt->value), cnt->prec.nb);
	}
	else
		cnt->prt_v = ft_strndup((char*)(cnt->value), strlen);
}

static void	pf_convert_content_number(t_content *cnt)
{
	if (cnt->type == 'i' || cnt->type == 'd')
		pf_convert_integer(cnt, T_SIGNED, 10);
	if (cnt->type == 'u')
		pf_convert_uinteger(cnt, T_UNSIGNED, 10);
	if (cnt->type == 'p')
		cnt->flags = cnt->flags | PF_FLAG_SHARP;
	if (cnt->type == 'x' || cnt->type == 'X' || cnt->type == 'p')
		pf_convert_uinteger(cnt, T_UNSIGNED, 16);
}

char			*convert_char(char c)
{
	char	*str;

	str = (char*)malloc(sizeof(char) * (1));
	if (!str)
		return (NULL);
	if (c == '\0')
		c = '*';
	str[0] = c;
	str[1] = '\0';
	return (str);
}

void		pf_convert_content(t_content *cnt)
{
	pf_convert_content_number(cnt);
	if (cnt->type == 's')
		pf_convert_string(cnt);
	if (cnt->type == 'c')
		cnt->prt_v = convert_char((char)*(int*)(cnt->value));
	if (cnt->type == '%')
		cnt->prt_v = strdup("%");
	if (cnt->type == 'X')
		ft_strtoupper(cnt->prt_v);
	pf_flags_add(cnt);
}

void		pf_convertlist(t_list **lst)
{
	t_list *tmp;

	tmp = *lst;
	while (tmp)
	{
		pf_convert_content((tmp)->content);
		(tmp) = tmp->next;
	}
}
