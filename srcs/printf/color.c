/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:33:41 by iwillens          #+#    #+#             */
/*   Updated: 2024/05/31 23:14:16 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_color(char *buf, size_t idx)
{
	char	*begin;
	char	*end;
	size_t	index;
	size_t	i;
	char	*c;

	index = idx / 2;
	c = "reset/bold/light/black/red/green/yellow/blue/magenta/cyan/white/";
	ft_bzero(buf, COLOR_BUFFER_SIZE);
	begin = c;
	end = ft_strchr(c, '/');
	i = 0;
	while (i < index && begin && end)
	{
		begin = end + 1;
		end = ft_strchr(begin, '/');
		i++;
	}
	if (!begin || !end)
		return ;
	*buf++ = '[';
	if (idx % 2)
		buf += ft_strlcpy(buf, "bright", 7);
	ft_strlcpy(buf, begin, end - begin + 1);
	buf[end - begin] = ']';
}

size_t	parse_color(const char *str, t_printf *printf)
{
	char	buf[COLOR_BUFFER_SIZE];
	size_t	i;

	++str;
	i = 0;
	while (i < N_COLORS * 2)
	{
		get_color(buf, i);
		if (!ft_strncmp(str, buf, ft_strlen(buf)))
		{
			printf->color = 1;
			if (i <= 2)
				printf->color = 0;
			printf->cnt.value.u = i;
			return (ft_strlen(buf));
		}
		i++;
	}
	printf->error = 1;
	return (fatal("Invalid color", 0));
}

void	process_color(t_printf *printf)
{
	t_content	*cnt;
	size_t		index;

	index = printf->cnt.value.u / 2;
	cnt = &printf->cnt;
	if (index >= INDEX_FIRST_COLOR)
	{
		index += FIRST_COLOR - INDEX_FIRST_COLOR;
		if (cnt->type == 'B')
			index += DIFF_FOREGROUND_BACKGROUND;
		if (cnt->value.u % 2)
			index += DIFF_NORMAL_BRIGHT;
	}
	storestr("\033[", printf);
	storenumber(index, PF_BASE_10, printf);
	storechar('m', printf);
}
