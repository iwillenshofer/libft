/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flagshandling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 11:33:26 by iwillens          #+#    #+#             */
/*   Updated: 2024/05/31 09:42:05 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	getflags(const char *str, int *flags)
{
	size_t	pos;

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

size_t	getwidth(const char *str, int *number)
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
