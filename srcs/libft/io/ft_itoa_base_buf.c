/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_buf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:49:47 by iwillens          #+#    #+#             */
/*   Updated: 2024/05/31 11:04:42 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static ssize_t	handle_signal(long long n,
	unsigned long long *dst_nbr, size_t base_len, char *buf)
{
	if (n < 0 && base_len == 10)
	{
		buf[0] = '-';
		*dst_nbr = (unsigned long long)(-n);
		return (1);
	}
	*dst_nbr = (unsigned long long)n;
	return (0);
}

static ssize_t	recursive_print(unsigned long long nbr,
	char *base, char *buf, size_t pos)
{
	size_t	base_len;

	base_len = ft_strlen(base);
	if (nbr >= base_len)
	{
		pos = recursive_print(nbr / base_len, base, buf, pos);
		buf[pos] = base[nbr % base_len];
		return (pos + 1);
	}
	buf[pos] = base[nbr % base_len];
	return (pos + 1);
}

/*
** prints a number according to base, being the base
** the lenght a string with the characters to be used.
** if no base is passed, base 10 is used
** returns the number of characters in the buffer.
** returns -1 on error
*/

ssize_t	ft_itoa_base_buf(long long n, char *base, char *buf)
{
	unsigned long long		nbr;
	int						count;
	size_t					base_len;

	if (!base)
		base = "0123456789";
	base_len = ft_strlen(base);
	if (base_len < 2)
		return (-1);
	count = handle_signal(n, &nbr, base_len, buf);
	count += recursive_print(nbr, base, buf, count);
	buf[count] = '\0';
	return (count);
}
