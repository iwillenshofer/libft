/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:04:57 by iwillens          #+#    #+#             */
/*   Updated: 2024/05/31 11:25:24 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# define GNL_RDFAIL		0
# define GNL_RDSUCCESS	1
# define GNL_RDLAST		2

typedef enum e_bool
{
	E_FALSE,
	E_TRUE
}	t_bool;

char	*get_next_line(int fd);

#endif
