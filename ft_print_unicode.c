/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unicode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 08:34:23 by iwillens          #+#    #+#             */
/*   Updated: 2020/02/07 22:47:59 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"
/*
** checks how many bits the integer is using
** so that we know how many characters (bytes) we'll need to
** print our unicode
*/

static size_t	bit_counter(int c)
{
	size_t counter;

	counter = 0;
	if (c < 0)
		c = ~c;
	while (c)
	{
		c = c >> 1;
		counter++;
	}
	return (counter);
}

/*
** return the ammount of bytes needs to represent an
** ammount of bits.
** count starts at 0 (1 byte will return 0);
** The bytes needed to fit the UTF-8 are the 'x's
** displayed in the comment below.
*/

static size_t	bits_to_bytes(size_t bits)
{
	if (bits < 8)
		return (0);
	else if (bits <= 11)
		return (1);
	else if (bits <= 16)
		return (2);
	else if (bits <= 21)
		return (3);
	else if (bits <= 27)
		return (4);
	else
		return (5);
}

/*
** the following function returns the header byte mask,
** according to the following table (UTF standard)
** and returns the first char of the charset,
** shifting the leftmost position to the rightmost
** position (>> n times)
** 1 byte:  0xxxxxxx
** 2 bytes: 110xxxxx
** 3 bytes: 1110xxxx
** 4 bytes: 11110xxx
*/

static char		header_chr(int c, size_t bytes)
{
	char mask[6];

	if (bytes == 0)
		return (c);
	mask[0] = 0b00000000;
	mask[1] = 0b11000000;
	mask[2] = 0b11100000;
	mask[3] = 0b11110000;
	mask[4] = 0b11111000;
	mask[5] = 0b11111100;
	c = c >> (bytes * 6);
	c = c | mask[bytes];
	return (c);
}

/*
** the following function returns the
** mask for all other bytes:
** 10xxxxxx;
** it first removes all other bytes we won't use
** by using a mask, then shifts the right byte to the
** right (according to the ammount of bytes needed and the
** position we're in)
*/

static char		following_chr(int c, size_t bytes, size_t index)
{
	char	mask;

	mask = 0b00111111;
	c = c >> ((bytes - index) * 6);
	c = (c & mask);
	mask = 0b10000000;
	c = c | mask;
	return (c);
}

int				ft_print_unicode(int c, int fd)
{
	size_t	i;
	char	chr;
	size_t	bytes;

	bytes = bits_to_bytes(bit_counter(c));
	i = 0;
	while (i <= bytes)
	{
		if (i == 0)
			chr = header_chr(c, bytes);
		else
			chr = following_chr(c, bytes, i);
		write(fd, &chr, 1);
		i++;
	}
	return (0);
}

/*
** if limit_1 is enable, 
** it uses one single byte;
*/

char *ft_chr_unicode(wchar_t c, int limit_1)
{
	size_t	i;
	char	chr;
	size_t	bytes;
	char 	*str;

	if (c == 0)
		c = '*';
	if (limit_1)
		bytes = 0;
	else
		bytes = bits_to_bytes(bit_counter(c));
	str = (char*)malloc(sizeof(char) * (bytes + 2));
	i = 0;
	while (i <= bytes)
	{
		if (i == 0)
			chr = header_chr(c, bytes);
		else
			chr = following_chr(c, bytes, i);
		str[i] = chr;
		i++;
	}
	str[bytes + 1] = '\0';
	return (str);
}