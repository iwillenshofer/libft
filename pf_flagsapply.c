/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_flagsapply.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 21:43:22 by iwillens          #+#    #+#             */
/*   Updated: 2020/02/08 22:35:58 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_flags_add_sharp(t_content *cnt)
{
//	if (cnt->type == 'p')

//		cnt->printable_value = ft_insertchr_start(cnt->printable_value, '0');
//		cnt->printable_value = ft_insertchr_start(cnt->printable_value, '1');
	if (cnt->type == 'o')
		cnt->printable_value = ft_insertchr_start(cnt->printable_value, '0');
	else if (cnt->type == 'x' || cnt->type == 'p')
	{
		cnt->printable_value = ft_insertchr_start(cnt->printable_value, 'x');
		cnt->printable_value = ft_insertchr_start(cnt->printable_value, '0');
	}
	else if (cnt->type == 'X')
	{
		cnt->printable_value = ft_insertchr_start(cnt->printable_value, 'X');
		cnt->printable_value = ft_insertchr_start(cnt->printable_value, '0');
	}

}

void	pf_flags_add_plus(t_content *cnt)
{
	if (cnt->printable_value[0] != '-')
		cnt->printable_value = ft_insertchr_start(cnt->printable_value, '+');

}

void	pf_flags_add_space(t_content *cnt)
{
	if (cnt->printable_value[0] != '-' &&
		cnt->printable_value[0] != '+')
		cnt->printable_value = ft_insertchr_start(cnt->printable_value, ' ');
}

void	pf_flags_padding(t_content *cnt)
{	
	size_t str_len;
	size_t width;
	
	str_len = ft_strlen(cnt->printable_value);
	if ((int)cnt->width.number < 0)
	{
		cnt->width.number = ft_negative_topositive((int)cnt->width.number);
		cnt->flags = cnt->flags ^ PF_FLAG_MINUS;
	}
	else if (cnt->printable_value[0] == '-' && cnt->width.number > 0 && 
		str_len > 0 && cnt->flags & PF_FLAG_ZERO && cnt->precision.wildcard == 2)
		cnt->width.number -= 1;
	width = cnt->width.number;

	if (cnt->padding_char == '0' && !(cnt->flags & PF_FLAG_MINUS))
		cnt->printable_value = ft_fillnchr_start(cnt->printable_value, cnt->padding_char, width);
	else
		while (str_len < width)
		{
			if (cnt->flags & PF_FLAG_MINUS)
				cnt->printable_value = ft_insertchr_end(cnt->printable_value, ' ');
			else
				cnt->printable_value = ft_insertchr_start(cnt->printable_value, cnt->padding_char);
			width--;
		}
}

void pf_flags_add(t_content *cnt)
{
	if (cnt->width.number < 0)
	{
		cnt->flags = cnt->flags | PF_FLAG_MINUS;
		cnt->width.number = ft_negative_topositive(cnt->width.number);
		if (cnt->flags & PF_FLAG_ZERO)
			cnt->width.number += 1;
	}
	if (cnt->flags & PF_FLAG_SHARP)
		pf_flags_add_sharp(cnt);
	if (cnt->flags & PF_FLAG_PLUS)
		pf_flags_add_plus(cnt);
	if (cnt->flags & PF_FLAG_SPACE)
		pf_flags_add_space(cnt);
	if (cnt->width.number > 0)
	{
		if (cnt->flags & PF_FLAG_ZERO && !(cnt->precision.wildcard != PF_WILDCARD_DEFAULT))
			cnt->padding_char = '0';
		else
			cnt->padding_char = ' ';
		pf_flags_padding(cnt);
	}
}