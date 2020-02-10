/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 17:44:57 by iwillens          #+#    #+#             */
/*   Updated: 2020/02/10 08:29:22 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	countdigits(unsigned long long int n, size_t base)
{
	size_t count;

	count = 1;
	while (n >= base)
	{
		count++;
		n = n / base;
	}
	return (count);
}

static char		*fillnumber(unsigned int isnegative,
		unsigned long long int number, size_t base)
{
	char	*str;
	size_t	digits;

	digits = isnegative + countdigits(number, base);
	if (!(str = (char*)malloc(digits + 1)))
		return (NULL);
	str[digits] = '\0';
	while (digits)
	{
		str[digits - 1] = (number % base) + '0';
		if (str[digits - 1] > '9')
			str[digits - 1] += ('a' - ':');
		number = number / base;
		digits -= 1;
	}
	if (isnegative)
		str[0] = '-';
	return (str);
}

char			*ft_itoa_base(long long int n, size_t base, char optsigned)
{
	char					*tmp;
	unsigned long long int	number;
	int						isnegative;

	(void)base;
	isnegative = 0;
	if (optsigned == 1 && n < 0)
	{
		number = (unsigned long long int)(n * -1);
		isnegative = 1;
	}
	else
		number = (unsigned long long int)n;
	tmp = fillnumber(isnegative, number, base);
	return (tmp);
}
