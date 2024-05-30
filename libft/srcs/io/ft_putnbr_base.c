/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:49:47 by iwillens          #+#    #+#             */
/*   Updated: 2024/05/29 16:46:24 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putchar_fd_count(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

/*
** prints a number according to base, being the base
** the lenght a string with the characters to be used.
** if no base is passed, base 10 is used
** returns the number of characters printed.
*/

size_t	ft_putnbr_base(long long n, char *base, int fd)
{
	unsigned long long		nbr;
	int						count;
	size_t					base_len;

	if (!base)
		base = "0123456789";
	base_len = ft_strlen(base);
	count = 0;
	if (n < 0 && base_len == 10)
	{
		nbr = (unsigned long long)(-n);
		count += ft_putchar_fd_count('-', fd);
	}
	else
	{
		nbr = (unsigned long long)n;
	}
	if (nbr >= (unsigned long long)base_len)
	{
		count += ft_putnbr_base(nbr / base_len, base, fd);
		count += ft_putchar_fd_count(base[nbr % base_len], fd);
	}
	else
		count += ft_putchar_fd_count(base[nbr], fd);
	return (count);
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
