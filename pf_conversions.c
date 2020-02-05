/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_conversions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 17:40:23 by iwillens          #+#    #+#             */
/*   Updated: 2020/02/05 07:35:15 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void pf_convert_float(t_content *content)
{
	if (content->precision.number > 0)
		content->printable_value = 
			ft_ftoa_base(*(double*)(content->value), content->precision.number);
	else if (content->precision.wildcard == PF_WILDCARD_SET)
		content->printable_value = 
			ft_ftoa_base(*(double*)(content->value), 0);
	else
		content->printable_value = 
			ft_ftoa_base(*(double*)(content->value), 6);
}

void pf_convert_integer(t_content *content, short type, size_t base)
{
	content->printable_value = 
		ft_itoa_base(*(long long int*)(content->value), base, type);
	if (content->precision.number > 0)
		content->printable_value = ft_fillnchr_start(content->printable_value, '0',
			content->precision.number);
	else if (content->precision.wildcard == PF_WILDCARD_SET &&
		ft_strncmp(content->printable_value, "0",
			ft_strlen(content->printable_value)) == 0)
		content->printable_value = "";

}

void pf_convert_content(t_content *content)
{
	short type;
	
	type = T_SIGNED;
	if (content->type == 'i' || content->type == 'd')
		pf_convert_integer(content, T_SIGNED, 10);
	if (content->type == 'u')
		pf_convert_integer(content, T_UNSIGNED, 10);
	if (content->type == 'o')
		pf_convert_integer(content, T_UNSIGNED, 8);
	if (content->type == 'x' || content->type == 'X')
		pf_convert_integer(content, T_UNSIGNED, 16);
	if (content->type == 'X')
		ft_strtoupper(content->printable_value);
	if ((content->type == 'f' || content->type == 'F'))
		pf_convert_float(content);
	if (content->type == 's')
		content->printable_value = (char*)(content->value);
}

void pf_convertlist(t_list **lst)
{
	t_list *tmp;
	tmp = *lst;
	while (tmp)
	{
		pf_convert_content((tmp)->content);
		(tmp) = tmp->next;
	}
}
