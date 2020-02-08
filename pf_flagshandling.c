/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_flagshandling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 11:33:26 by iwillens          #+#    #+#             */
/*   Updated: 2020/02/06 02:08:22 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	pf_getflags(char *str, int *flags)
{
	size_t pos;

	pos = 0;
	*flags = 0;
	str++;
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

size_t	pf_getwidth(char *str, int *number)
{
	size_t	pos;
	char	*nbstr;

	pos = 0;
	*number = 0;
	while (ft_isdigit(str[pos]))
		pos++;
	if (pos != 0)
	{
		nbstr = (char*)malloc(sizeof(char) * (pos + 1));
		ft_memcpy(nbstr, str, pos);
		nbstr[pos] = '\0';
		*number = ft_atoi(nbstr);
		free(nbstr);
	}
	return (pos);
}

size_t	pf_getlength(char *str, int *length)
{
	size_t pos;

	pos = 0;
	*length = 0;
	if (*str == 'l' && str[1] == 'l')
		*length |= LM_LONGLONG;
	else if (*str == 'l')
		*length |= LM_LONG;
	else if (*str == 'h' && str[1] == 'h')
		*length |= LM_CHAR;
	else if (*str == 'h')
		*length |= LM_SHORT;
	else if (*str == 'j')
		*length |= LM_INTMAX;
	else if (*str == 'z')
		*length |= LM_SIZE_T;
	else if (*str == 't')
		*length |= LM_PTRDIFF;
	else if (*str == 'L')
		*length |= LM_LONGDBL;
	if (*length)
		pos++;
	if (*length & LM_LONGLONG || *length & LM_CHAR)
		pos++;
	return (pos);
}
