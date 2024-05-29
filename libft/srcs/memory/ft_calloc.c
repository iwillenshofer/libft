/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 17:40:30 by iwillens          #+#    #+#             */
/*   Updated: 2024/05/28 17:19:14 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t			i;
	size_t			tot_bytes;
	unsigned char	*mem;

	i = 0;
	tot_bytes = count * size;
	mem = (unsigned char *)malloc(tot_bytes);
	if (!mem)
		return (NULL);
	while (i < tot_bytes)
	{
		mem[i] = 0;
		i++;
	}
	return (mem);
}
