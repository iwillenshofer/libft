/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:06:07 by iwillens          #+#    #+#             */
/*   Updated: 2024/05/30 17:18:37 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	printcontent(t_printf *printf)
{
	if (printf->cnt.type == 's')
		process_string(printf);
	else if (printf->cnt.type == 'c')
		process_char(printf);
	else if (printf->cnt.type == 'd' || printf->cnt.type == 'i')
		process_int(printf);
	else if (printf->cnt.type == 'u' || printf->cnt.type == 'x' || printf->cnt.type == 'X' || printf->cnt.type == 'p')
		process_uint(printf);
}
/*
** This function is responsible for parsing the precision flag
** if there is a '.'
*/
static const char		*parse_precision(const char *str, t_content *cnt,
	int number)
{
	if (*str == '.')
	{
		str++;
		str += getwidth(str, &number);
		cnt->prec.nb = number;
		if (number == 0 && *str == '*')
		{
			cnt->prec.wc = PF_WC_AP;
			str++;
		}
		else
			cnt->prec.wc = PF_WC_SET;
	}
	return (str);
}

/*
** go through the whole string passed by the user (%...s)
** to check for flags, width, precision, modifier and specifier.
*/
static int		setcontent(const char *str, t_content *cnt)
{
	int		flags;
	int		number;

	str += getflags(str, &flags);
	cnt->flags = flags;
	str += getwidth(str, &number);
	cnt->width.nb = number;
	if (number == 0 && *str == '*')
	{
		cnt->width.wc = PF_WC_AP;
		str++;
	}
	else
		cnt->width.wc = PF_WC_SET;
	str = parse_precision(str, cnt, number);
	if (*str != cnt->type)
		return (fatal_specifier(cnt->type, *str));
	return (PRINTF_SUCCESS);
}

/*
** This function is responsible for performing the substitution of the
** specifiers in the string.
*/
int	perform_substitution(const char **str, va_list *ap, t_printf *printf)
{
	int			counter;
	size_t		pos;

	(void)ap;
	counter = 0;
	ft_bzero(&(printf->cnt), sizeof(t_content));
	pos = ft_strfind_first(*str, PF_SPECIFIERS);
	if (!pos)
		return (fatal(ERR_UNTERMINATED_SPEC, 1));
	printf->cnt.type = *(*str + (pos - 1));
	if (setcontent(*str, &printf->cnt) == PRINTF_FAILURE)
		return (PRINTF_FAILURE);
	get_values(ap, &printf->cnt);
	printcontent(printf);
	*str += pos;
	counter += printf->cnt.counter;
	if (printf->cnt.error)
		return (fatal(ERR_PRINTINGERROR, 0));
	return (counter);
}

/*
** the main function for a printf without allocation.
*/
int	ft_printf(const char *str, ...)
{
	va_list		ap;
	int			ret;
	t_printf	printf;

	ft_bzero(&printf, sizeof(t_printf));
	printf.counter = 0;
	va_start(ap, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			ret = perform_substitution(&str, &ap, &printf);
			if (ret == PRINTF_FAILURE)
				return (PRINTF_FAILURE);
			printf.counter += ret;
		}
		else
		{
			if (printchar(*str, &printf) == PRINTF_FAILURE)
				return (PRINTF_FAILURE);
			printf.counter++;
			str++;
		}
	}
	dump_buffer(&printf);
	va_end(ap);
	return (printf.counter);
}
