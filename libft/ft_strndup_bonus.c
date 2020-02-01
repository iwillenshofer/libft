/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 16:02:07 by iwillens          #+#    #+#             */
/*   Updated: 2020/01/30 16:20:02 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>
#include "libft.h"

char    *ft_strndup(const char *s1, size_t n)
{
	size_t	i;
	size_t	tot_bytes;
	char	*mem;

	tot_bytes = ft_strlen(s1);
	if (n < tot_bytes)
		tot_bytes = n;
	tot_bytes+=1;

	i = 0;
	if (!(mem = (char*)malloc(tot_bytes)))
		return (NULL);
	while (i < tot_bytes)
	{
		mem[i] = s1[i];
		i++;
	}
	mem[tot_bytes] = '\0';
	return (mem);
}
