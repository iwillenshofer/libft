/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 13:44:57 by iwillens          #+#    #+#             */
/*   Updated: 2024/05/28 17:43:54 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*s_src;
	unsigned char	*s_dst;

	if ((dst == NULL && src == NULL) || len == 0)
		return (dst);
	s_dst = (unsigned char *)dst;
	s_src = (unsigned char *)src;
	if (s_dst > s_src)
	{
		i = len;
		while (i--)
			s_dst[i] = s_src[i];
	}
	else
	{
		i = 0;
		while (i < len)
		{
			s_dst[i] = s_src[i];
			i++;
		}
	}
	return (dst);
}
