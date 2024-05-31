/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 16:02:07 by iwillens          #+#    #+#             */
/*   Updated: 2024/05/28 17:01:12 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	size_t	i;
	size_t	tot_bytes;
	char	*mem;

	tot_bytes = ft_strlen(s1) + 1;
	if (n < tot_bytes)
		tot_bytes = n;
	i = 0;
	mem = (char *)malloc(tot_bytes + 1);
	if (!mem)
		return (NULL);
	while (i < tot_bytes)
	{
		mem[i] = s1[i];
		i++;
	}
	mem[tot_bytes] = '\0';
	return (mem);
}
