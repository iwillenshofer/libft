/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_flagshandling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 11:33:26 by iwillens          #+#    #+#             */
/*   Updated: 2024/05/29 11:11:50 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	pf_getflags(const char *str, int *flags)
{
	size_t pos;

	pos = 0;
	*flags = 0;
	while (*str)
	{
		if (*str == '-')
			*flags |= PF_FLAG_MINUS;
		else if (*str == '+')
			*flags |= PF_FLAG_PLUS;
		else if (*str == ' ')
			*flags |= PF_FLAG_SPACE;
		else if (*str == '#')
			*flags |= PF_FLAG_SHARP;
		else if (*str == '0')
			*flags |= PF_FLAG_ZERO;
		else
			return (pos);
		pos++;
		str++;
	}
	return (pos);
}

size_t	pf_getwidth(const char *str, int *number)
{
	size_t	pos;

	pos = 0;
	*number = 0;
	while (ft_isdigit(str[pos]))
		pos++;
	if (pos != 0)
		*number = ft_atoi(str);
	return (pos);
}

