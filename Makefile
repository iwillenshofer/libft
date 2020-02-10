# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/04 01:52:48 by iwillens          #+#    #+#              #
#    Updated: 2020/02/10 11:17:59 by iwillens         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCS =  ft_printf.c \
		pf_contenthandling.c \
		pf_conversions.c \
		pf_errorhandling.c \
		pf_flagshandling.c \
		pf_flagsapply.c \
		ft_print_unicode.c \
		pf_stringhandling.c \
		pf_freemem.c \
		pf_flagspadding.c \
		pf_conversionsinteger.c \
		pf_conversionsfloat.c \
		pf_vaarg.c

OBJS = $(patsubst %.c, %.o, $(SRCS))

all :  $(NAME)

$(NAME) : $(OBJS) 
	cd libft; make all
	cp libft/libft.a ./$(NAME)
	ar -rc $(NAME) $(OBJS) 

OBJS : $(SRCS) 
	gcc -c -Wall -Wextra -Werror $(SRCS) -o $(OBJS) 


bonus : all
	
clean: 
	@rm -f $(OBJS) $(OBJSLIBFT)
	@cd libft; make clean;

fclean : clean
	@rm -f $(NAME)
	@cd libft; make fclean;

re : fclean libftprintf.a
