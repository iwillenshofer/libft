/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:35:13 by iwillens          #+#    #+#             */
/*   Updated: 2024/05/30 10:45:20 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t printnumber(long long n, char *base, t_content *content)
{
	ssize_t ret;

	if (content->error)
		return (PRINTF_FAILURE);
	ret = ft_putnbr_base(n, base, 1);
	if (ret == PRINTF_FAILURE)
	{
		if (content)
			content->error = 1;
		return (PRINTF_FAILURE);
	}
	if (content)
		content->counter += ret;
	return (ret);
}
/*
** helper functions for printing
*/
ssize_t	printchar(char c, t_content *content)
{
	ssize_t	ret;

	if (content->error)
		return (PRINTF_FAILURE);
	ret = ft_putchar_fd_count(c, 1);
	if (ret == PRINTF_FAILURE)
	{
		if (content)
			content->error = 1;
		return (PRINTF_FAILURE);
	}
	if (content)
		content->counter++;
	return (ret);
}

ssize_t	printnchar(char c, int n, t_content *content)
{
	ssize_t ret;

	while (n--)
	{
		ret = printchar(c, content);
		if (ret == PRINTF_FAILURE)
			return (PRINTF_FAILURE);
	}
	return (ret);
}

ssize_t	printnstr(char *str, int n, t_content *content)
{
	ssize_t ret;

	while (*str && n--)
	{
		ret = printchar(*str, content);
		if (ret == PRINTF_FAILURE)
			return (PRINTF_FAILURE);
		str++;
	}
	return (ret);
}

ssize_t	printstr(char *str, t_content *content)
{
	ssize_t ret;

	while (*str)
	{
		ret = printchar(*str, content);
		if (ret == PRINTF_FAILURE)
			return (PRINTF_FAILURE);
		str++;
	}
	return (ret);
}
