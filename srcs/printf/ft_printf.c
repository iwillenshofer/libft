/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:06:07 by iwillens          #+#    #+#             */
/*   Updated: 2024/05/31 09:39:40 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	t_printf	printf;

	ft_bzero(&printf, sizeof(t_printf));
	printf.fd = 1;
	printf.type = T_PRINTF;
	va_start(printf.ap, str);
	return (inner_printf(str, &printf));
}

int	ft_snprintf(char *dest, size_t size, const char *str, ...)
{
	t_printf	printf;
	int			ret;

	ft_bzero(&printf, sizeof(t_printf));
	printf.type = T_SNPRINTF;
	printf.str = ft_strdup("");
	if (!(printf.str))
		return (PRINTF_FAILURE);
	va_start(printf.ap, str);
	ret = inner_printf(str, &printf);
	if (ret == PRINTF_FAILURE)
	{
		free(printf.str);
		return (PRINTF_FAILURE);
	}
	ft_memcpy(dest, printf.str, size);
	free(printf.str);
	return (ret);
}

int	ft_asprintf(char **ret, const char *str, ...)
{
	t_printf	printf;
	int			ret_val;

	ft_bzero(&printf, sizeof(t_printf));
	printf.type = T_ASPRINTF;
	printf.str = ft_strdup("");
	if (!(printf.str))
		return (PRINTF_FAILURE);
	va_start(printf.ap, str);
	ret_val = inner_printf(str, &printf);
	if (ret_val == PRINTF_FAILURE)
	{
		free(printf.str);
		*ret = NULL;
		return (PRINTF_FAILURE);
	}
	*ret = printf.str;
	return (ret_val);
}

int	ft_dprintf(int fd, const char *str, ...)
{
	t_printf	printf;

	ft_bzero(&printf, sizeof(t_printf));
	printf.fd = fd;
	printf.type = T_DPRINTF;
	va_start(printf.ap, str);
	return (inner_printf(str, &printf));
}
