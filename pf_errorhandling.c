/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_errorhandling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 11:07:19 by iwillens          #+#    #+#             */
/*   Updated: 2020/02/07 22:23:17 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_strerr_unterminated(void)
{
	ft_putstr_fd("**** UNTERMINATED!!! What now?!?! ***\n", 1);
}

void	pf_strerr_invalidspecifier(char expected, char found)
{
	ft_putstr_fd("ERRO: Identificador não conhecido-->", 1);
	ft_putchar_fd(expected, 1);
	ft_putchar_fd(found, 1);
	ft_putstr_fd("\n", 1);
}
