/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 14:44:34 by iwillens          #+#    #+#             */
/*   Updated: 2024/05/31 11:15:51 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** reads the file until \n is found (or eof)
*/
int	read_file(int fd, char **s, char **buf, t_bool *found)
{
	int		ret;
	char	*tmp;

	ret = 1;
	while (ret && !(*found))
	{
		ret = read(fd, *buf, BUFFER_SIZE);
		if (ret < 0)
		{
			free(*buf);
			return (GNL_RDFAIL);
		}
		(*buf)[ret] = 0;
		if (ft_strchr(*buf, '\n'))
			*found = E_TRUE;
		tmp = *s;
		*s = ft_strjoin(*s, *buf);
		free(tmp);
		if (!*s)
		{
			free(*buf);
			return (GNL_RDFAIL);
		}
	}
	return (GNL_RDSUCCESS);
}

int	read_line(int fd, char **s)
{
	char	*buf;
	t_bool	found;

	found = E_FALSE;
	if (ft_strchr(*s, '\n'))
		return (GNL_RDSUCCESS);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (GNL_RDFAIL);
	if (read_file(fd, s, &buf, &found) == GNL_RDFAIL)
		return (GNL_RDFAIL);
	free(buf);
	if (found)
		return (GNL_RDSUCCESS);
	return (GNL_RDLAST);
}

char	*success(char **buf)
{
	char		*s;
	char		*tmp;
	char		*linebreak;

	linebreak = ft_strchr(*buf, '\n');
	tmp = *buf;
	*buf = ft_strdup(linebreak + 1);
	*(linebreak + 1) = 0;
	s = ft_strdup(tmp);
	if (!s)
	{
		free(*buf);
		*buf = NULL;
	}
	free(tmp);
	return (s);
}

char	*lastline(char **buf)
{
	char		*s;

	s = ft_strdup(*buf);
	free(*buf);
	if (!s || !(ft_strlen(s)))
	{
		free(s);
		s = NULL;
	}
	*buf = NULL;
	return (s);
}

char	*get_next_line(int fd)
{
	static char	*buf[OPEN_MAX];
	int			ret;

	if (fd < 0 || fd >= OPEN_MAX)
		return (NULL);
	if (!buf[fd])
		buf[fd] = ft_strdup("");
	if (!buf[fd])
		return (NULL);
	ret = read_line(fd, &buf[fd]);
	if (ret == GNL_RDSUCCESS)
		return (success(&buf[fd]));
	else if (ret == GNL_RDLAST)
		return (lastline(&buf[fd]));
	free(buf[fd]);
	buf[fd] = NULL;
	return (NULL);
}
