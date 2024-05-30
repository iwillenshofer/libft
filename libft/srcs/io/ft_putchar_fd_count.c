/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd_count.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:07:34 by iwillens          #+#    #+#             */
/*   Updated: 2024/05/30 10:19:06 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** writes a character to the given file descriptor
** returns the number of characters written
** returns -1 on error
*/
ssize_t	ft_putchar_fd_count(char c, int fd)
{
	ssize_t ret;

	ret = write(fd, &c, 1);
	return (ret);
}
