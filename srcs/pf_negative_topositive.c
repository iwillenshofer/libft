/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_negative_topositive.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 13:19:30 by iwillens          #+#    #+#             */
/*   Updated: 2024/05/28 23:32:56 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_printf.h"
/*
** This functions returns 0 if the number is negative,
**	or the original number it received if it is positive or 0;
*/

int	pf_negative_tozero(int n)
{
	if (n < 0)
		return (0);
	else
		return (n);
}

int	pf_negative_topositive(int n)
{
	if (n < 0)
		return (n * -1);
	else
		return (n);
}
