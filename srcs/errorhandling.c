/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorhandling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:57:52 by iwillens          #+#    #+#             */
/*   Updated: 2024/05/30 12:04:16 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	fatal(char *msg, int silent)
{
	if (silent)
		return (PRINTF_FAILURE);
	ft_putstr_fd("fatal error: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putchar_fd('\n', 2);
	return (PRINTF_FAILURE);
}

int fatal_specifier(char expected, char found)
{
	ft_putstr_fd("fatal error: invalid specifier '", 2);
	ft_putchar_fd(found, 2);
	ft_putstr_fd("'. expected: '", 2);
	ft_putchar_fd(expected, 2);
	ft_putstr_fd("'\n", 2);
	return (PRINTF_FAILURE);
}
