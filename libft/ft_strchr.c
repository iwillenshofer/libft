/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 17:23:40 by iwillens          #+#    #+#             */
/*   Updated: 2020/01/21 20:12:49 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned int i;

	i = 0;
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char*)s);
		s++;
	}
	if (*s == '\0' && (char)c == '\0')
		return ((char*)s);
	return (NULL);
}
