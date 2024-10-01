/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_startswith.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 20:40:14 by iwillens          #+#    #+#             */
/*   Updated: 2024/09/27 20:43:13 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool	ft_startswith(const char *str, const char *prefix)
{
	if (!str || !prefix)
		return (false);
	return (!ft_strncmp(str, prefix, ft_strlen(prefix)));
}
