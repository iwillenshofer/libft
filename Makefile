# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/01 10:55:01 by iwillens          #+#    #+#              #
#    Updated: 2024/05/31 12:07:00 by iwillens         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# *** Main Definitions                                                         #
# **************************************************************************** #

NAME = libft.a

CC = clang
CCFLAGS = -Wall -Werror -Wextra

SRC_DIR = ./srcs

LIBFT_SRC_DIR = ${SRC_DIR}/libft
PRINTF_SRC_DIR = ${SRC_DIR}/printf
GNL_SRC_DIR = ${SRC_DIR}/gnl

OBJ_DIR = ./build
INCLUDE_DIRS = ./includes
INCLUDES = $(addprefix -I, $(INCLUDE_DIRS))

LIBFT_SRCS = 	${LIBFT_SRC_DIR}/strings/ft_strnstr.c \
				${LIBFT_SRC_DIR}/strings/ft_strlcpy.c \
				${LIBFT_SRC_DIR}/strings/ft_strlen.c \
				${LIBFT_SRC_DIR}/strings/ft_itoa_base.c \
				${LIBFT_SRC_DIR}/strings/ft_strchr.c \
				${LIBFT_SRC_DIR}/strings/ft_striteri.c \
				${LIBFT_SRC_DIR}/strings/ft_strjoin.c \
				${LIBFT_SRC_DIR}/strings/ft_split.c \
				${LIBFT_SRC_DIR}/strings/ft_strrchr.c \
				${LIBFT_SRC_DIR}/strings/ft_substr.c \
				${LIBFT_SRC_DIR}/strings/ft_strncmp.c \
				${LIBFT_SRC_DIR}/strings/ft_strmapi.c \
				${LIBFT_SRC_DIR}/strings/ft_strtrim.c \
				${LIBFT_SRC_DIR}/strings/ft_strndup.c \
				${LIBFT_SRC_DIR}/strings/ft_strlcat.c \
				${LIBFT_SRC_DIR}/strings/ft_strdup.c \
				${LIBFT_SRC_DIR}/strings/ft_strtoupper.c \
				${LIBFT_SRC_DIR}/strings/ft_atoi.c \
				${LIBFT_SRC_DIR}/strings/ft_itoa.c \
				${LIBFT_SRC_DIR}/char/ft_isdigit.c \
				${LIBFT_SRC_DIR}/char/ft_isblank.c \
				${LIBFT_SRC_DIR}/char/ft_isascii.c \
				${LIBFT_SRC_DIR}/char/ft_isprint.c \
				${LIBFT_SRC_DIR}/char/ft_toupper.c \
				${LIBFT_SRC_DIR}/char/ft_isalpha.c \
				${LIBFT_SRC_DIR}/char/ft_islower.c \
				${LIBFT_SRC_DIR}/char/ft_isupper.c \
				${LIBFT_SRC_DIR}/char/ft_isalnum.c \
				${LIBFT_SRC_DIR}/char/ft_isspace.c \
				${LIBFT_SRC_DIR}/char/ft_tolower.c \
				${LIBFT_SRC_DIR}/memory/ft_memcmp.c \
				${LIBFT_SRC_DIR}/memory/ft_bzero.c \
				${LIBFT_SRC_DIR}/memory/ft_memcpy.c \
				${LIBFT_SRC_DIR}/memory/ft_memccpy.c \
				${LIBFT_SRC_DIR}/memory/ft_memchr.c \
				${LIBFT_SRC_DIR}/memory/ft_memset.c \
				${LIBFT_SRC_DIR}/memory/ft_memmove.c \
				${LIBFT_SRC_DIR}/memory/ft_calloc.c \
				${LIBFT_SRC_DIR}/lists/ft_lstadd_back.c \
				${LIBFT_SRC_DIR}/lists/ft_lstnew.c \
				${LIBFT_SRC_DIR}/lists/ft_lstlast.c \
				${LIBFT_SRC_DIR}/lists/ft_lstclear.c \
				${LIBFT_SRC_DIR}/lists/ft_lstiter.c \
				${LIBFT_SRC_DIR}/lists/ft_lstmap.c \
				${LIBFT_SRC_DIR}/lists/ft_lstsize.c \
				${LIBFT_SRC_DIR}/lists/ft_lstadd_front.c \
				${LIBFT_SRC_DIR}/lists/ft_lstdelone.c \
				${LIBFT_SRC_DIR}/io/ft_putstr_fd.c \
				${LIBFT_SRC_DIR}/io/ft_putnbr.c \
				${LIBFT_SRC_DIR}/io/ft_putnbr_fd.c \
				${LIBFT_SRC_DIR}/io/ft_putendl.c \
				${LIBFT_SRC_DIR}/io/ft_putendl_fd.c \
				${LIBFT_SRC_DIR}/io/ft_putchar.c \
				${LIBFT_SRC_DIR}/io/ft_putchar_fd.c \
				${LIBFT_SRC_DIR}/io/ft_putstr.c \
				${LIBFT_SRC_DIR}/io/ft_putnbr_base.c \
				${LIBFT_SRC_DIR}/io/ft_putchar_fd_count.c \
				${LIBFT_SRC_DIR}/io/ft_itoa_base_buf.c \
				${LIBFT_SRC_DIR}/addons/ft_ishex.c \
				${LIBFT_SRC_DIR}/addons/ft_arglen.c \
				${LIBFT_SRC_DIR}/addons/ft_sqrt.c \
				${LIBFT_SRC_DIR}/addons/ft_notnumeric.c \
				${LIBFT_SRC_DIR}/addons/ft_nothex.c \
				${LIBFT_SRC_DIR}/addons/ft_puthex.c \
				${LIBFT_SRC_DIR}/addons/ft_strcpy.c \
				${LIBFT_SRC_DIR}/addons/ft_atoul.c \
				${LIBFT_SRC_DIR}/addons/ft_putbytes.c \
				${LIBFT_SRC_DIR}/addons/ft_puthex_byte.c \
				${LIBFT_SRC_DIR}/addons/ft_strcmp.c


PRINTF_SRCS =	${PRINTF_SRC_DIR}/buffer.c \
				${PRINTF_SRC_DIR}/flagshandling.c \
				${PRINTF_SRC_DIR}/print.c \
				${PRINTF_SRC_DIR}/process_string.c \
				${PRINTF_SRC_DIR}/ft_printf.c \
				${PRINTF_SRC_DIR}/errorhandling.c \
				${PRINTF_SRC_DIR}/vaarg.c \
				${PRINTF_SRC_DIR}/process_uint.c \
				${PRINTF_SRC_DIR}/inner_printf.c \
				${PRINTF_SRC_DIR}/process_int.c

GNL_SRCS =		${GNL_SRC_DIR}/get_next_line.c

SRCS := $(GNL_SRCS) $(PRINTF_SRCS) $(LIBFT_SRCS)

OBJS := $(SRCS:${SRC_DIR}/%.c=${OBJ_DIR}/%.o)
DEPS := $(OBJS:.o=.d)

# **************************************************************************** #
# *** Main Rules                                                               #
# **************************************************************************** #

all : $(NAME)

${NAME} : ${OBJS} Makefile
	@ar -r ${NAME} ${OBJS}
	@echo "\033[95m${NAME} is built. \033[0m"

${OBJ_DIR}/%.o: $(SRC_DIR)/%.c Makefile
	@mkdir -p ${@D}
	@${CC} ${CCFLAGS} -MMD -c $< ${INCLUDES} -o $@

# **************************************************************************** #
# *** Common Rules                                                             #
# **************************************************************************** #

clean:
	@rm -rf ${OBJ_DIR}

fclean: clean
	@rm -rf ./${NAME}

re: fclean all

-include $(DEPENDS)
