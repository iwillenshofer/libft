/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 17:44:57 by iwillens          #+#    #+#             */
/*   Updated: 2020/02/03 20:23:06 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	countdigits(unsigned long long int n, size_t base)
{
	size_t count;

	count = 1;
	while (n > base)
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
	while (digits--)
	{
		str[digits] = (number % base) + '0';
		if(str[digits] > '9')
			str[digits] += ('a' - ':');
		number = number / base;
	}
	if (isnegative)
		str[0] = '-';
	return (str);
}

char			*ft_itoa_base(long long int n, size_t base, char optsigned)
{

	unsigned long long int	number;
	int					isnegative;

	(void)base;
	isnegative = 0;
	if (optsigned == 1 && n < 0)
	{
		number = (unsigned long long int)(-n);
		isnegative = 1;
	}
	else
		number = (unsigned long long int)n;
	return (fillnumber(isnegative, number, base));
}
