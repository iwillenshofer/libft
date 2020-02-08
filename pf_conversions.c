/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_conversions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 17:40:23 by iwillens          #+#    #+#             */
/*   Updated: 2020/02/07 22:47:04 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void pf_convert_float(t_content *content)
{
	if (content->precision.number > 0)
		content->printable_value = 
			ft_ftoa_base(*(double*)(content->value), content->precision.number);
	else if (content->precision.wildcard == PF_WILDCARD_SET )
		content->printable_value = 
			ft_ftoa_base(*(double*)(content->value), 0);
	else
		content->printable_value = 
			ft_ftoa_base(*(double*)(content->value), 6);
}

void pf_convert_integer(t_content *cnt, short type, size_t base)
{
	if (!cnt->length && ft_strchr(PF_SPEC_INT, cnt->type))
	cnt->printable_value = 
		ft_itoa_base(*(int*)(cnt->value), base, type);
	else
	cnt->printable_value = 
		ft_itoa_base(*(long long int*)(cnt->value), base, type);
	if (cnt->precision.number > 0)
		cnt->printable_value = ft_fillnchr_start(cnt->printable_value, '0',
			cnt->precision.number);
	else if ((cnt->precision.wildcard == PF_WILDCARD_SET) &&
		ft_strncmp(cnt->printable_value, "0",
			ft_strlen(cnt->printable_value)) == 0)
		cnt->printable_value[0] = '\0';
}

void pf_convert_uinteger(t_content *cnt, short type, size_t base)
{
	if (!cnt->length && ft_strchr(PF_SPEC_UINT, cnt->type))
	cnt->printable_value = 
		ft_itoa_base(*(unsigned int*)(cnt->value), base, type);
	else
	cnt->printable_value = 
		ft_itoa_base(*(unsigned long long int*)(cnt->value), base, type);
	if (cnt->precision.number > 0)
		cnt->printable_value = ft_fillnchr_start(cnt->printable_value, '0',
			cnt->precision.number);
	else if (cnt->precision.wildcard == PF_WILDCARD_SET &&
		ft_strncmp(cnt->printable_value, "0",
			ft_strlen(cnt->printable_value)) == 0)
		cnt->printable_value[0] = '\0';

}

void pf_convert_string(t_content *cnt)
{
	size_t strlen;
	size_t i;
	char *str;

	i = 0;
	
	str = cnt->printable_value;
	strlen = ft_strlen(cnt->value);
	if ((cnt->precision.wildcard == (PF_WILDCARD_SET) || cnt->precision.wildcard == (PF_WILDCARD_AP)) && 
		(size_t)cnt->precision.wildcard < strlen && cnt->precision.number >= 0)
		{
			cnt->printable_value = ft_strndup((char*)(cnt->value), cnt->precision.number);
		}	

		else
			cnt->printable_value = ft_strndup((char*)(cnt->value), strlen);
}

void pf_convert_content(t_content *content)
{
	short type;
	
	type = T_SIGNED;
	if (content->type == 'i' || content->type == 'd')
		pf_convert_integer(content, T_SIGNED, 10);
	if (content->type == 'u')
		pf_convert_uinteger(content, T_UNSIGNED, 10);
	if (content->type == 'p')
		content->flags = content->flags | PF_FLAG_SHARP;
	if (content->type == 'o')
		pf_convert_uinteger(content, T_UNSIGNED, 8);
	if (content->type == 'x' || content->type == 'X' || content->type == 'p')
		pf_convert_uinteger(content, T_UNSIGNED, 16);
	if (content->type == 'X')
		ft_strtoupper(content->printable_value);
	if ((content->type == 'f' || content->type == 'F'))
		pf_convert_float(content);
	if (content->type == 's')
		pf_convert_string(content);
	if (content->type == 'c')
		{
			//content->printable_value = ft_char_tostr(*(wchar_t*)content->value);
			content->printable_value = ft_chr_unicode(*(wchar_t*)(content->value), 1);
		}
	if (content->type == '%')
		content->printable_value = strdup("%");
	pf_flags_add(content);
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
