/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inner_printf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:52:49 by iwillens          #+#    #+#             */
/*   Updated: 2024/05/31 22:49:12 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	printcontent(t_printf *printf)
{
	if (printf->cnt.type == 's')
		process_string(printf);
	else if (printf->cnt.type == 'c')
		process_char(printf);
	else if (printf->cnt.type == 'd' || printf->cnt.type == 'i')
		process_int(printf);
	else if (printf->cnt.type == 'u' || printf->cnt.type == 'x'
		|| printf->cnt.type == 'X' || printf->cnt.type == 'p')
		process_uint(printf);
	else if (printf->cnt.type == 'C' || printf->cnt.type == 'B')
		process_color(printf);
}

/*
** This function is responsible for parsing the precision flag
** if there is a '.'
*/
static const char	*parse_precision(const char *str,
	t_content *cnt, int number)
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
static int	setcontent(const char *str, t_printf *printf)
{
	int			flags;
	int			number;
	t_content	*cnt;

	cnt = &printf->cnt;
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
	if (printf->error)
		return (PRINTF_FAILURE);
	if (*str != cnt->type)
		return (fatal_specifier(cnt->type, *str));
	return (PRINTF_SUCCESS);
}

/*
** This function is responsible for performing the substitution of the
** specifiers in the string.
*/
static int	perform_substitution(const char **str, t_printf *printf)
{
	int			counter;
	size_t		pos;

	counter = 0;
	ft_bzero(&(printf->cnt), sizeof(t_content));
	pos = ft_strfind_first(*str, PF_SPECIFIERS);
	if (!pos)
		return (fatal(ERR_UNTERMINATED_SPEC, 1));
	printf->cnt.type = *(*str + (pos - 1));
	if (setcontent(*str, printf) == PRINTF_FAILURE)
		return (PRINTF_FAILURE);
	get_values(&printf->ap, &printf->cnt);
	if (printf->cnt.type == 'C' || printf->cnt.type == 'B')
		*str += parse_color(*str, printf);
	printcontent(printf);
	*str += pos;
	counter += printf->cnt.counter;
	return (counter);
}

int	inner_printf(const char *str, t_printf *printf)
{
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			printf->counter += perform_substitution(&str, printf);
		}
		else
		{
			storechar(*str, printf);
			printf->counter++;
			str++;
		}
		if (printf->error)
			break ;
	}
	if (printf->color)
		storenstr(RESET, ft_strlen(RESET), printf);
	dump_buffer(printf);
	if (printf->error)
		printf->counter = -1;
	va_end(printf->ap);
	return (printf->counter);
}
