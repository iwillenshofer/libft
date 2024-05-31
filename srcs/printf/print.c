/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:35:13 by iwillens          #+#    #+#             */
/*   Updated: 2024/05/31 09:41:46 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** storesnumber - store a number in the buffer
*/
ssize_t	storenumber(long long n, char *base, t_printf *printf)
{
	ssize_t		ret;
	t_content	*cnt;

	dump_if_needed(printf);
	cnt = &printf->cnt;
	if (printf->error)
		return (PRINTF_FAILURE);
	ret = ft_itoa_base_buf(n, base, &printf->buffer[printf->buffer_pos]);
	printf->buffer_pos += ret;
	if (ret == PRINTF_FAILURE)
	{
		if (cnt)
			printf->error = 1;
		return (PRINTF_FAILURE);
	}
	if (cnt)
		cnt->counter += ret;
	return (ret);
}

/*
** helper functions for storing characters and strings
** in the buffer
*/
ssize_t	storechar(char c, t_printf *printf)
{
	t_content	*cnt;

	dump_if_needed(printf);
	cnt = &printf->cnt;
	if (printf->error)
		return (PRINTF_FAILURE);
	printf->buffer[printf->buffer_pos] = c;
	printf->buffer_pos++;
	if (cnt)
		cnt->counter++;
	return (1);
}

ssize_t	storenchar(char c, int n, t_printf *printf)
{
	ssize_t	ret;

	while (n--)
	{
		ret = storechar(c, printf);
		if (ret == PRINTF_FAILURE)
			return (PRINTF_FAILURE);
	}
	return (ret);
}

ssize_t	storenstr(char *str, int n, t_printf *printf)
{
	ssize_t	ret;

	while (*str && n--)
	{
		ret = storechar(*str, printf);
		if (ret == PRINTF_FAILURE)
			return (PRINTF_FAILURE);
		str++;
	}
	return (ret);
}

ssize_t	storestr(char *str, t_printf *printf)
{
	ssize_t	ret;

	while (*str)
	{
		ret = storechar(*str, printf);
		if (ret == PRINTF_FAILURE)
			return (PRINTF_FAILURE);
		str++;
	}
	return (ret);
}
