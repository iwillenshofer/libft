/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_stringhandling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 04:39:03 by iwillens          #+#    #+#             */
/*   Updated: 2020/02/07 20:20:12 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void pf_writecharstr(char *s)
{
	int i;
	char c;
	i = 0;

	while (s && s[i] != '\0')
	{
		c = s[i];
		if (c == '*')
			c = 0;
		ft_putchar_fd(c, 1);
		i++;
	}
}

char *pf_strchecknull(char *str)
{
	if (!str)
		return ("(null)");
	else
		return (str);
}