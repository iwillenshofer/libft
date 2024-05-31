/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:49:47 by iwillens          #+#    #+#             */
/*   Updated: 2024/05/30 13:07:10 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static ssize_t	handle_signal(long long n,
	unsigned long long *dst_nbr, size_t base_len, int fd)
{
	ssize_t	ret;

	ret = 0;
	if (n < 0 && base_len == 10)
	{
		ret = ft_putchar_fd_count('-', fd);
		if (ret == -1)
			return (-1);
		*dst_nbr = (unsigned long long)(-n);
		return (ret);
	}
	*dst_nbr = (unsigned long long)n;
	return (ret);
}

static ssize_t	recursive_print(unsigned long long nbr,
	char *base, size_t base_len, int fd)
{
	ssize_t	ret;

	if (nbr >= base_len)
	{
		ret = recursive_print(nbr / base_len, base, base_len, fd);
		if (ret == -1)
			return (-1);
		if (ft_putchar_fd_count(base[nbr % base_len], fd) == -1)
			return (-1);
		return (ret + 1);
	}
	if (ft_putchar_fd_count(base[nbr], fd) == -1)
		return (-1);
	return (1);
}

/*
** prints a number according to base, being the base
** the lenght a string with the characters to be used.
** if no base is passed, base 10 is used
** returns the number of characters printed.
** returns -1 on error
*/

ssize_t	ft_putnbr_base(long long n, char *base, int fd)
{
	unsigned long long		nbr;
	int						count;
	size_t					base_len;
	ssize_t					ret;

	if (!base)
		base = "0123456789";
	base_len = ft_strlen(base);
	if (base_len < 2)
		return (-1);
	count = handle_signal(n, &nbr, base_len, fd);
	if (count == -1)
		return (-1);
	ret = recursive_print(nbr, base, base_len, fd);
	if (ret == -1)
		return (-1);
	return (count + ret);
}

size_t	ft_numlen_base(long long n, char *base)
{
	size_t					len;
	unsigned long long		nbr;
	size_t					base_len;

	if (!base)
		base = "0123456789";
	base_len = ft_strlen(base);
	len = 1;
	if (n < 0 && base_len == 10)
	{
		nbr = (unsigned long long)(-n);
		len++;
	}
	else
	{
		nbr = (unsigned long long)n;
	}
	while (nbr >= base_len)
	{
		nbr /= base_len;
		len++;
	}
	return (len);
}
