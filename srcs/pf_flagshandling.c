/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_flagshandling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 11:33:26 by iwillens          #+#    #+#             */
/*   Updated: 2024/05/28 23:53:23 by iwillens         ###   ########.fr       */
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
		if (!nbstr)
			return (0);
		ft_memcpy(nbstr, str, pos);
		nbstr[pos] = '\0';
		*number = ft_atoi(nbstr);
		free(nbstr);
	}
	return (pos);
}

