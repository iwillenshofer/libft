/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 07:34:52 by iwillens          #+#    #+#             */
/*   Updated: 2024/05/28 17:21:40 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	unsigned int	chr;

	chr = (unsigned int)c;
	if (chr >= 32 && chr < 127)
		return (1);
	return (0);
}
