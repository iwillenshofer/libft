/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:47:03 by iwillens          #+#    #+#             */
/*   Updated: 2024/05/30 17:13:51 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	dump_if_needed(t_printf *printf)
{
	if (printf->buffer_pos >= PRINTF_BUFFER_SIZE - PRINFT_BUFFERNB_SIZE)
		dump_buffer(printf);
}

void	dump_buffer(t_printf *printf)
{
	if (write(1, printf->buffer, printf->buffer_pos) == -1)
		printf->cnt.error = 1;
	printf->buffer_pos = 0;
}
