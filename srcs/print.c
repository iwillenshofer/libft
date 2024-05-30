/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:35:13 by iwillens          #+#    #+#             */
/*   Updated: 2024/05/30 17:17:03 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t printnumber(long long n, char *base, t_printf *printf)
{
	ssize_t ret;
	t_content *cnt;

	dump_if_needed(printf);
	cnt = &printf->cnt;
	if (cnt->error)
		return (PRINTF_FAILURE);
	ret = ft_itoa_base_buf(n, base, &printf->buffer[printf->buffer_pos]);
	printf->buffer_pos += ret;
	if (ret == PRINTF_FAILURE)
	{
		if (cnt)
			cnt->error = 1;
		return (PRINTF_FAILURE);
	}
	if (cnt)
		cnt->counter += ret;
	return (ret);
}
/*
** helper functions for printing
*/
ssize_t	printchar(char c, t_printf *printf)
{
	t_content *cnt;

	dump_if_needed(printf);
	cnt = &printf->cnt;
	if (cnt->error)
		return (PRINTF_FAILURE);
	//ret = ft_putchar_fd_count(c, 1);
	printf->buffer[printf->buffer_pos] = c;
	printf->buffer_pos++;
	if (cnt)
		cnt->counter++;
	return (1);
}

ssize_t	printnchar(char c, int n, t_printf *printf)
{
	ssize_t ret;

	while (n--)
	{
		ret = printchar(c, printf);
		if (ret == PRINTF_FAILURE)
			return (PRINTF_FAILURE);
	}
	return (ret);
}

ssize_t	printnstr(char *str, int n, t_printf *printf)
{
	ssize_t ret;

	while (*str && n--)
	{
		ret = printchar(*str, printf);
		if (ret == PRINTF_FAILURE)
			return (PRINTF_FAILURE);
		str++;
	}
	return (ret);
}

ssize_t	printstr(char *str, t_printf *printf)
{
	ssize_t ret;

	while (*str)
	{
		ret = printchar(*str, printf);
		if (ret == PRINTF_FAILURE)
			return (PRINTF_FAILURE);
		str++;
	}
	return (ret);
}
