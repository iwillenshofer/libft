/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:06:07 by iwillens          #+#    #+#             */
/*   Updated: 2024/05/29 19:48:16 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#include <stdio.h>

int	fatal(char *msg)
{
	ft_putstr_fd("Fatal error: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putchar_fd('\n', 2);
	return (PRINTF_FAILURE);
}

int fatal_specifier(char expected, char found)
{
	ft_putstr_fd("error: invalid specifier", 2);
	ft_putchar_fd(expected, 2);
	ft_putchar_fd(found, 2);
	ft_putstr_fd("\n", 2);
	return (PRINTF_FAILURE);
}

void process_char(t_content *cnt)
{
    char padding_char;
    int padding;

    padding_char = ' ';
    padding = 0;
    if (cnt->flags & PF_FLAG_ZERO && !(cnt->flags & PF_FLAG_MINUS))
        padding_char = '0';
    if (cnt->width.nb > 1)
        padding = cnt->width.nb - 1;
    if (!(cnt->flags & PF_FLAG_MINUS))
        printnchar(padding_char, padding, cnt);
    printchar(cnt->value.i, cnt);
    if ((cnt->flags & PF_FLAG_MINUS))
        printnchar(padding_char, padding, cnt);
}

/*
** printing functions
*/
void	process_string(t_content *cnt)
{
	char padding_char;
	size_t padding;
	size_t	len;
	char *tmp;

	tmp = cnt->value.s;
	len = 0;
	padding = 0;
	padding_char = ' ';
	while (*tmp && (!(cnt->prec.wc) || (len < cnt->prec.nb)))
	{
		len++;
		tmp++;
	}
	if (cnt->flags & PF_FLAG_ZERO && cnt->flags & PF_FLAG_MINUS)
		padding_char = '0';

	if (cnt->width.nb > len)
		padding = cnt->width.nb - len;
	if (!(cnt->flags & PF_FLAG_MINUS))
		printnchar(padding_char, padding, cnt);
	printnstr(cnt->value.s, len, cnt);
	if ((cnt->flags & PF_FLAG_MINUS))
		printnchar(padding_char, padding, cnt);
}

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
		str += pf_getwidth(str, &number);
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
	str += pf_getflags(str, &flags);
	content->flags = flags;
	str += pf_getwidth(str, &number);
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
		return (fatal(ERR_UNTERMINATED_SPEC));
	content.type = *(*str + (pos - 1));
	setcontent(*str, &content);
	get_values(ap, &content);
	printcontent(&content);
	*str += pos;
	counter += content.counter;
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
				return (counter);
			counter += ret;
		}
		else
		{
			ft_putchar_fd(*str, 1);
			counter++;
			str++;
		}
	}
	va_end(ap);
	return (counter);
}
