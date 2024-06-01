/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:47:03 by iwillens          #+#    #+#             */
/*   Updated: 2024/05/31 23:00:18 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	dump_if_needed(t_printf *printf)
{
	if (printf->buffer_pos >= PRINTF_BUFFER_SIZE - PRINFT_BUFFERNB_SIZE)
		dump_buffer(printf);
}

int	buffer_to_str(t_printf *printf)
{
	char	*tmp;

	tmp = malloc(printf->str_size + printf->buffer_pos + 1);
	if (!tmp)
		return (PRINTF_FAILURE);
	ft_memcpy(tmp, printf->str, printf->str_size);
	ft_memcpy(tmp + printf->str_size, printf->buffer, printf->buffer_pos);
	tmp[printf->str_size + printf->buffer_pos] = '\0';
	free(printf->str);
	printf->str = tmp;
	printf->str_size += printf->buffer_pos;
	return (PRINTF_SUCCESS);
}

void	dump_buffer(t_printf *printf)
{
	if (printf->error)
		return ;
	if (printf->type == T_PRINTF || printf->type == T_DPRINTF)
	{
		if (write(printf->fd, printf->buffer, printf->buffer_pos) == -1)
			printf->error = 1;
	}
	else if (printf->type == T_SNPRINTF || printf->type == T_ASPRINTF)
	{
		if (buffer_to_str(printf) == PRINTF_FAILURE)
			printf->error = 1;
	}
	else
		printf->error = 1;
	printf->buffer_pos = 0;
}
