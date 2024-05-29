/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_freemem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 22:42:21 by iwillens          #+#    #+#             */
/*   Updated: 2024/05/28 23:54:16 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** initialize the structs variables
*/

void	pf_fillblank(t_content **content)
{
	(*content)->flags = 0;
	(*content)->width.nb = 0;
	(*content)->width.wc = 0;
	(*content)->width.was_negative = 0;
	(*content)->prec.was_negative = 0;
	(*content)->prec.nb = 0;
	(*content)->prec.wc = PF_WC_DEFAULT;
	(*content)->pad_chr = ' ';
	(*content)->value = 0;
	(*content)->length = 0;
	(*content)->prt_v = 0;
}

void	pf_freecontent(t_content **cnt)
{
	free((*cnt)->prt_v);
	if ((*cnt)->value && (*cnt)->type != 's')
		free((*cnt)->value);
	free((*cnt)->orig_content);
	free(*cnt);
}

void	pf_freelist(t_list **lst)
{
	t_content	*cnt;
	t_list		*tmp;

	while (*lst)
	{
		cnt = (*lst)->content;
		pf_freecontent(&cnt);
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp);
	}
	free(*lst);
}
