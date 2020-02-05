/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 20:09:31 by iwillens          #+#    #+#             */
/*   Updated: 2020/02/01 09:22:38 by MacbookAi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> 
#include "ft_printf.h"
#include <unistd.h>
int	main(void)
{
	signed int pointer;
	//pointer = (signed int*)malloc(sizeof(signed int) * 1);
	char *specifiers;
	specifiers = ft_strndup(PF_SPECIFIERS, sizeof(PF_SPECIFIERS));
	long long a;
	a = 3;
	int i;
	i = 0;
	char val[4];
	val[0] = '\n';
	val[1] = '%';
while (specifiers[i])
{
		val[2] = specifiers[i];
		write(1, val, 3);

write(1, "\n", 1);
	if (specifiers[i] == 'n')
		printf("geeks%n\n", &pointer);
	else if (specifiers[i] == 's')
		printf("geeks%s\n", "abc");
	else
		printf(val, a);
	write(1, "\n", 1);
	
	i++;
}

//	ft_printf("te%#3283.n\%ci%%iIgor \tWillen%sho%zi%z%itei", 33, 3);
//	printf("%214.i", 3);
	return (0);

}
