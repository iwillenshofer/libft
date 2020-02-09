/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_freemem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 22:42:21 by iwillens          #+#    #+#             */
/*   Updated: 2020/02/08 22:01:26 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** used to initialize the structs variables
** to allow null test before freeing it at the end
*/

void		pf_fillblank(t_content **content)
{
	(*content)->flags = 0;
	(*content)->width.number = 0;
	(*content)->width.wildcard = 0;
	(*content)->precision.number = 0;
	(*content)->precision.wildcard = PF_WILDCARD_DEFAULT;
	(*content)->padding_char = ' ';
	(*content)->value = 0;
	(*content)->length = 0;
	(*content)->printable_value = 0;
}
void	pf_freecontent(t_content **cnt)
{
	if ((*cnt)->printable_value)
		free((*cnt)->printable_value);
	if ((*cnt)->value && (*cnt)->type != 's')
		free((*cnt)->value);
	if ((*cnt)->orig_content)
		free((*cnt)->orig_content);
	free(*cnt);
}
void pf_freelist(t_list **lst)
{
	t_content *cnt;
	t_list *tmp;

	while (*lst)
	{
		cnt = (*lst)->content;
		pf_freecontent(&cnt);
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp);
	}
	if(*lst)
		free(*lst);
}