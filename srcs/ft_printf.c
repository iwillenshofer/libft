/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:06:07 by iwillens          #+#    #+#             */
/*   Updated: 2024/05/30 12:06:29 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	printcontent(t_content *content)
{
	if (content->type == 's')
		process_string(content);
	else if (content->type == 'c')
		process_char(content);
	else if (content->type == 'd' || content->type == 'i')
		process_int(content);
	else if (content->type == 'u' || content->type == 'x' || content->type == 'X' || content->type == 'p')
		process_uint(content);
}
/*
** This function is responsible for parsing the precision flag
** if there is a '.'
*/
static const char		*parse_precision(const char *str, t_content *content,
	int number)
{
	if (*str == '.')
	{
		str++;
		str += getwidth(str, &number);
		content->prec.nb = number;
		if (number == 0 && *str == '*')
		{
			content->prec.wc = PF_WC_AP;
			str++;
		}
		else
			content->prec.wc = PF_WC_SET;
	}
	return (str);
}

/*
** go through the whole string passed by the user (%...s)
** to check for flags, width, precision, modifier and specifier.
*/
static int		setcontent(const char *str, t_content *content)
{
	int		flags;
	int		number;
	str += getflags(str, &flags);
	content->flags = flags;
	str += getwidth(str, &number);
	content->width.nb = number;
	if (number == 0 && *str == '*')
	{
		content->width.wc = PF_WC_AP;
		str++;
	}
	else
		content->width.wc = PF_WC_SET;
	str = parse_precision(str, content, number);
	if (*str != content->type)
		return (fatal_specifier(content->type, *str));
	return (PRINTF_SUCCESS);
}

/*
** This function is responsible for performing the substitution of the
** specifiers in the string.
*/
int	perform_substitution(const char **str, va_list *ap)
{
	t_content	content;
	int			counter;
	size_t		pos;

	(void)ap;
	counter = 0;
	ft_bzero(&content, sizeof(t_content));
	pos = ft_strfind_first(*str, PF_SPECIFIERS);
	if (!pos)
		return (fatal(ERR_UNTERMINATED_SPEC, 1));
	content.type = *(*str + (pos - 1));
	if (setcontent(*str, &content) == PRINTF_FAILURE)
		return (PRINTF_FAILURE);
	get_values(ap, &content);
	printcontent(&content);
	*str += pos;
	counter += content.counter;
	if (content.error)
		return (fatal(ERR_PRINTINGERROR, 0));
	return (counter);
}

/*
** the main function for a printf without allocation.
*/
int	ft_printf(const char *str, ...)
{
	va_list		ap;
	int			counter;
	int			ret;

	counter = 0;
	va_start(ap, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			ret = perform_substitution(&str, &ap);
			if (ret == PRINTF_FAILURE)
				return (PRINTF_FAILURE);
			counter += ret;
		}
		else
		{
			if (ft_putchar_fd_count(*str, 1) == PRINTF_FAILURE)
				return (PRINTF_FAILURE);
			counter++;
			str++;
		}
	}
	va_end(ap);
	return (counter);
}
