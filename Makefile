# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/01 10:55:01 by iwillens          #+#    #+#              #
#    Updated: 2024/05/30 17:13:37 by iwillens         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# *** Main Definitions                                                         #
# **************************************************************************** #

NAME = libftprintf.a

CC = clang
CCFLAGS = -Wall -Werror -Wextra# -fsanitize=address -g

SRC_DIR = ./srcs/
OBJ_DIR = ./build
INCLUDE_DIRS = . ./libft/
INCLUDES = $(addprefix -I, $(INCLUDE_DIRS))

SRCS = ${SRC_DIR}/process_int.c \
		${SRC_DIR}/process_uint.c \
		${SRC_DIR}/process_string.c \
		${SRC_DIR}/errorhandling.c \
		${SRC_DIR}/print.c \
		${SRC_DIR}/flagshandling.c \
		${SRC_DIR}/ft_printf.c \
		${SRC_DIR}/vaarg.c \
		${SRC_DIR}/buffer.c
#		${SRC_DIR}/pf_negative_topositive.c \
#		${SRC_DIR}/pf_errorhandling.c \
#		${SRC_DIR}/pf_flagsapply.c \
#		${SRC_DIR}/pf_stringhandling.c \
#		${SRC_DIR}/pf_insertchr.c \
#		${SRC_DIR}/pf_flagspadding.c \
#		${SRC_DIR}/pf_contenthandling.c

OBJS = $(SRCS:${SRC_DIR}/%.c=${OBJ_DIR}/%.o)
DEPS = $(OBJS:.o=.d)
# **************************************************************************** #
# *** Libft Definitions                                                        #
# **************************************************************************** #
LIBFT_DIR = ./libft
LIBFT = ${LIBFT_DIR}/libft.a


# **************************************************************************** #
# *** Main Rules                                                               #
# **************************************************************************** #

all : ${NAME}

bonus: all

${NAME}: ${OBJS} Makefile ${LIBFT}
	@cp ${LIBFT} ./${NAME}
	@ar -r ${NAME} ${OBJS}
	@echo "\033[95m${NAME} is built. \033[0m"

${OBJ_DIR}/%.o: $(SRC_DIR)/%.c
	@mkdir -p ${@D}
	@${CC} ${CCFLAGS} -MMD -c $< ${INCLUDES} -o $@

# **************************************************************************** #
# *** Libft Rules                                                              #
# **************************************************************************** #

${LIBFT}:
	@make -s -C ${LIBFT_DIR}
# **************************************************************************** #
# *** Common Rules                                                             #
# **************************************************************************** #

run: all
	gcc  -L. -lftprintf  -fsanitize=address -g test.c  && ./a.out

clean:
	@rm -rf ${OBJ_DIR}
	@make -C ${LIBFT_DIR} clean

fclean: clean
	@rm -rf ./${NAME}
	@make -C ${LIBFT_DIR} fclean

re: fclean all

-include $(DEPENDS)
