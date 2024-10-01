/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifiers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:57:04 by iwillens          #+#    #+#             */
/*   Updated: 2024/06/07 17:00:51 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

const char	*parse_modifier(const char *str, t_content *cnt)
{
	if (!ft_strchr(LENGTH_MODIFIERS, *str))
		return (str);
	if (*str == 'h')
		cnt->modifier = LM_SHORT;
	else if (*str == 'l')
		cnt->modifier = LM_LONG;
	str++;
	return (str);
}
