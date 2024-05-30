# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/01 10:55:01 by iwillens          #+#    #+#              #
#    Updated: 2024/05/29 15:52:18 by iwillens         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# *** Main Definitions                                                         #
# **************************************************************************** #

NAME = libft.a

CC = clang
CCFLAGS = -Wall -Werror -Wextra# -fsanitize=address -g

SRC_DIR = ./srcs
OBJ_DIR = ./build
INCLUDE_DIRS = .
INCLUDES = $(addprefix -I, $(INCLUDE_DIRS))

SRCS = ${SRC_DIR}/strings/ft_strnstr.c \
		${SRC_DIR}/strings/ft_strlcpy.c \
		${SRC_DIR}/strings/ft_strlen.c \
		${SRC_DIR}/strings/ft_itoa_base.c \
		${SRC_DIR}/strings/ft_strchr.c \
		${SRC_DIR}/strings/ft_striteri.c \
		${SRC_DIR}/strings/ft_strjoin.c \
		${SRC_DIR}/strings/ft_split.c \
		${SRC_DIR}/strings/ft_strrchr.c \
		${SRC_DIR}/strings/ft_substr.c \
		${SRC_DIR}/strings/ft_strncmp.c \
		${SRC_DIR}/strings/ft_strmapi.c \
		${SRC_DIR}/strings/ft_strtrim.c \
		${SRC_DIR}/strings/ft_strndup.c \
		${SRC_DIR}/strings/ft_strlcat.c \
		${SRC_DIR}/strings/ft_strdup.c \
		${SRC_DIR}/strings/ft_strtoupper.c \
		${SRC_DIR}/strings/ft_atoi.c \
		${SRC_DIR}/strings/ft_itoa.c \
		${SRC_DIR}/char/ft_isdigit.c \
		${SRC_DIR}/char/ft_isblank.c \
		${SRC_DIR}/char/ft_isascii.c \
		${SRC_DIR}/char/ft_isprint.c \
		${SRC_DIR}/char/ft_toupper.c \
		${SRC_DIR}/char/ft_isalpha.c \
		${SRC_DIR}/char/ft_islower.c \
		${SRC_DIR}/char/ft_isupper.c \
		${SRC_DIR}/char/ft_isalnum.c \
		${SRC_DIR}/char/ft_isspace.c \
		${SRC_DIR}/char/ft_tolower.c \
		${SRC_DIR}/memory/ft_memcmp.c \
		${SRC_DIR}/memory/ft_bzero.c \
		${SRC_DIR}/memory/ft_memcpy.c \
		${SRC_DIR}/memory/ft_memccpy.c \
		${SRC_DIR}/memory/ft_memchr.c \
		${SRC_DIR}/memory/ft_memset.c \
		${SRC_DIR}/memory/ft_memmove.c \
		${SRC_DIR}/memory/ft_calloc.c \
		${SRC_DIR}/lists/ft_lstadd_back.c \
		${SRC_DIR}/lists/ft_lstnew.c \
		${SRC_DIR}/lists/ft_lstlast.c \
		${SRC_DIR}/lists/ft_lstclear.c \
		${SRC_DIR}/lists/ft_lstiter.c \
		${SRC_DIR}/lists/ft_lstmap.c \
		${SRC_DIR}/lists/ft_lstsize.c \
		${SRC_DIR}/lists/ft_lstadd_front.c \
		${SRC_DIR}/lists/ft_lstdelone.c \
		${SRC_DIR}/io/ft_putstr_fd.c \
		${SRC_DIR}/io/ft_putnbr.c \
		${SRC_DIR}/io/ft_putnbr_fd.c \
		${SRC_DIR}/io/ft_putendl.c \
		${SRC_DIR}/io/ft_putendl_fd.c \
		${SRC_DIR}/io/ft_putchar.c \
		${SRC_DIR}/io/ft_putchar_fd.c \
		${SRC_DIR}/io/ft_putstr.c \
		${SRC_DIR}/io/ft_putnbr_base.c


OBJS = $(SRCS:${SRC_DIR}/%.c=${OBJ_DIR}/%.o)
DEPS = $(OBJS:.o=.d)

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
