/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_errorhandling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 11:07:19 by iwillens          #+#    #+#             */
/*   Updated: 2024/05/29 10:20:30 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_strerr_unterminated(void)
{
	ft_putstr_fd("error: unterminated specifier\n", 1);
}

void	pf_strerr_invalidspecifier(char expected, char found)
{
	ft_putstr_fd("error: invalid specifier", 1);
	ft_putchar_fd(expected, 1);
	ft_putchar_fd(found, 1);
	ft_putstr_fd("\n", 1);
}
