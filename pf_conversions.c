/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_conversions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 17:40:23 by iwillens          #+#    #+#             */
/*   Updated: 2020/02/08 20:10:20 by iwillens         ###   ########.fr       */
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
	if (ft_strchr(PF_SPEC_INT, cnt->type))
	{
		if (cnt->length == 0)
			cnt->printable_value = ft_itoa_base((int)(*(int*)(cnt->value) & 0xFFFFFFFF), base, type);
		else if (cnt->length == LM_CHAR)
			cnt->printable_value = ft_itoa_base((long long int)(*(long long int*)(cnt->value) & 0xFF), base, type);
		else if (cnt->length == LM_SHORT)
			cnt->printable_value = ft_itoa_base((long long int)(*(long long int*)(cnt->value) & 0xFFFF), base, type);
		else if (cnt->length == LM_LONG)
			cnt->printable_value = ft_itoa_base((long long int)(*(long long int*)(cnt->value) & 0xFFFFFFFFFFFFFFFF), base, type);
		else if (cnt->length == LM_LONGLONG || cnt->length == LM_LONGDBL)
			cnt->printable_value = ft_itoa_base((long long int)(*(long long int*)(cnt->value) & 0xFFFFFFFFFFFFFFFF), base, type);
		else if (cnt->length == LM_INTMAX)
			cnt->printable_value = ft_itoa_base((long long int)(*(uintmax_t*)(cnt->value) & 0xFFFFFFFF), base, type);
		else if (cnt->length == LM_SIZE_T)
			cnt->printable_value = ft_itoa_base((long long int)(*(size_t*)(cnt->value) & 0xFFFFFFFFFFFFFFFF), base, type);
		else if (cnt->length == LM_PTRDIFF)
			cnt->printable_value = ft_itoa_base((long long int)(*(ptrdiff_t*)(cnt->value) & 0xFFFFFFFFFFFFFFFF), base, type);
	}
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
	if ( ft_strchr(PF_SPEC_UINT, cnt->type))
		{
		if (cnt->length == 0)
			cnt->printable_value = ft_itoa_base(*(unsigned int*)(cnt->value) &  0xffffffffU, base, type);
		else if (cnt->length == LM_CHAR)
			cnt->printable_value = ft_itoa_base(*(unsigned long long int*)(cnt->value) & 0xffU , base, type);
		else if (cnt->length == LM_SHORT)
			cnt->printable_value = ft_itoa_base(*(unsigned long long int*)(cnt->value) & 0xffffU, base, type);
		else if (cnt->length == LM_LONG)
			cnt->printable_value = ft_itoa_base(*(unsigned long long int*)(cnt->value)  & 0xffffffffffffffffU, base, type);
		else if (cnt->length == LM_LONGLONG || cnt->length == LM_LONGDBL)
			cnt->printable_value = ft_itoa_base(*(unsigned long long int*)(cnt->value) & 0xffffffffffffffffU, base, type);
		else if (cnt->length == LM_INTMAX)
			cnt->printable_value = ft_itoa_base(*(uintmax_t*)(cnt->value) & 0xffffffffU, base, type);
		else if (cnt->length == LM_SIZE_T)
			cnt->printable_value = ft_itoa_base(*(size_t*)(cnt->value) & 0xffffffffffffffffU, base, type);
		else if (cnt->length == LM_PTRDIFF)
			cnt->printable_value = ft_itoa_base(*(ptrdiff_t*)(cnt->value) &  0xFFFFFFFFFFFFFFFFU, base, type);
	}
	else
	cnt->printable_value = 	ft_itoa_base(*(unsigned long long int*)(cnt->value), base, type);
	if (cnt->precision.number > 0)
		cnt->printable_value = ft_fillnchr_start(cnt->printable_value, '0',
			cnt->precision.number);
	else if (cnt->precision.wildcard == PF_WILDCARD_SET &&
		ft_strncmp(cnt->printable_value, "0",
			ft_strlen(cnt->printable_value)) == 0)
		cnt->printable_value[0] = '\0';

}

void pf_convert_mantissa(t_content *content)
{
	long double n_dbl;
	size_t counter;
	char *str1;
	char *str2;

	counter = 0;
	n_dbl = *(double*)(content->value);
	while ((long long int)n_dbl >= 10 || (long long int)n_dbl <= -10)
	{
		n_dbl = n_dbl / 10.0;
		counter++;
	}
	if (content->precision.number > 0)
		content->printable_value = 
			ft_ftoa_base(n_dbl, content->precision.number);
	else if (content->precision.wildcard == PF_WILDCARD_SET )
		content->printable_value = 
			ft_ftoa_base(n_dbl, 0);
	else
		content->printable_value = 
			ft_ftoa_base(n_dbl, 6);
	content->printable_value = ft_insertchr_end(content->printable_value, 'e');
	if (n_dbl >= 0.0)
		content->printable_value = ft_insertchr_end(content->printable_value, '+');
	else
		content->printable_value = ft_insertchr_end(content->printable_value, '-');
	str1 = content->printable_value;
	str2 = ft_itoa(counter);
	if (counter < 10)
		str2 = ft_insertchr_start(str2, '0');
	content->printable_value = ft_strjoin(str1, str2);
	if (str1)
		free(str1);
	if (str2)
		free(str2);
}

void pf_convert_shortest_floatmant(t_content *content)
{
	t_content *tmpcont;
	
	tmpcont = (t_content*)malloc(sizeof(t_content));
	pf_fillblank(&tmpcont);
	tmpcont->precision.number = content->precision.number;
	tmpcont->precision.wildcard = content->precision.wildcard;
	tmpcont->value = content->value;
	pf_convert_float(tmpcont);
	if (ft_strlen(tmpcont->printable_value) < ft_strlen(content->printable_value))
	{
		if (content->printable_value)
			free(content->printable_value);
		content->printable_value = tmpcont->printable_value;
	}
	else
	{
		if (tmpcont->printable_value)
			free(tmpcont->printable_value);
	}
	if (tmpcont)
		free(tmpcont);
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
	if ((content->type == 'f' || content->type == 'F'))
		pf_convert_float(content);
	if (content->type == 'e' || content->type == 'E' || content->type == 'g' || content->type == 'G')
		pf_convert_mantissa(content);
	if  (content->type == 'g' || content->type == 'G')
		pf_convert_shortest_floatmant(content);
	if (content->type == 's')
		pf_convert_string(content);
	if (content->type == 'c')
			content->printable_value = ft_chr_unicode(*(wchar_t*)(content->value), 1);
	if (content->type == '%')
		content->printable_value = strdup("%");
	if (content->type == 'n')
	{
		content->printable_value = strdup("");
		return ;
	}
	if (content->type == 'X' || content->type == 'F' || content->type == 'G')
		ft_strtoupper(content->printable_value);
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
