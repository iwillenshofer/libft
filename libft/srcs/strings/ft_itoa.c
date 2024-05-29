/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 17:44:57 by iwillens          #+#    #+#             */
/*   Updated: 2024/05/28 16:59:02 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	countdigits(unsigned int n)
{
	size_t	count;

	count = 1;
	while (n > 9)
	{
		count++;
		n = n / 10;
	}
	return (count);
}

static char	*fillnumber(char *str, unsigned int isnegative,
		unsigned int number, size_t digits)
{
	if (isnegative)
		str[0] = '-';
	str[digits] = '\0';
	while (digits--)
	{
		str[digits] = (number % 10) + '0';
		number = number / 10;
		if (digits == 1 && isnegative)
			break ;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char			*str;
	size_t			digits;
	unsigned int	number;
	int				isnegative;

	isnegative = 0;
	if (n < 0)
	{
		number = (n * -1);
		isnegative = 1;
	}
	else
		number = n;
	digits = isnegative + countdigits(number);
	str = (char *)malloc(digits + 1);
	if (!str)
		return (NULL);
	return (fillnumber(str, isnegative, number, digits));
}
