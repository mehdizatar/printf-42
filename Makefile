# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mzatar <mzatar@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/06 12:24:26 by mehdi             #+#    #+#              #
#    Updated: 2020/08/18 17:15:21 by mzatar           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES = ft_printf.c\
	printf_format.c\
	main.c\
	printf_utils.c\

OBJS = ${SOURCES:.c=.o}

NAME = libftprintf.a

CC = gcc

CFLAGS = -Werror -Wall -Wextra

.c.o:
		${CC} ${CFLAGS} -c $< -o $@

${NAME}: ${OBJS}
		ar rc ${NAME} ${OBJS}
		ranlib ${NAME}
		${CC} ${CFLAGS} ${NAME} ${OBJS} -L.

all: ${NAME}

RM = rm -f

clean: 
	${RM} ${OBJS}
	${RM} ${LIB}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY:	all clean fclean re