/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:35:13 by iwillens          #+#    #+#             */
/*   Updated: 2024/05/29 20:19:58 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
/*
** helper functions for printing
*/

void	printchar(char c, t_content *content)
{
	ft_putchar_fd(c, 1);
	content->counter++;
}

void	printnchar(char c, int n, t_content *content)
{
	while (n--)
	{
		ft_putchar_fd(c, 1);
		content->counter++;
	}
}

void	printnstr(char *str, int n, t_content *content)
{
	while (*str && n--)
	{
		ft_putchar_fd(*str, 1);
		content->counter++;
		str++;
	}
}

void	printstr(char *str, t_content *content)
{
	while (*str)
	{
		ft_putchar_fd(*str, 1);
		content->counter++;
		str++;
	}
}
