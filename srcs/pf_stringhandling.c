/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_stringhandling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 04:39:03 by iwillens          #+#    #+#             */
/*   Updated: 2024/05/29 12:32:09 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** in case it is a char, and the original char was /0,
** it was converted to *. This function will convert it back.
*/
void	pf_writecharstr(char *s)
{
	int		i;
	char	c;

	i = 0;
	while (s && s[i] != '\0')
	{
		c = s[i];
		if (c == '*')
			c = 0;
		ft_putchar_fd(c, 1);
		i++;
	}
}

/*
** conta a quantidade de caracteres em toda a lista
** para dar o retorno do printf.
*/

size_t	pf_countliststr(t_list **lst)
{
	t_content	*cnt;
	t_list		*tmp;
	size_t		count;

	count = 0;
	tmp = *lst;
	while (tmp)
	{
		cnt = (tmp)->content;
		if (cnt->type != '!')
			count += ft_strlen(cnt->prt_v);
		else
			count += ft_strlen(cnt->orig_content);
		tmp = tmp->next;
	}
	return (count);
}

char	*pf_strchecknull(char *str)
{
	if (!str)
		return (STR_NULL);
	else
		return (str);
}
