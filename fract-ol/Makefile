# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scorreia <scorreia@student.42lausanne.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/29 16:25:33 by scorreia          #+#    #+#              #
#    Updated: 2022/03/25 13:54:35 by scorreia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
SRCS			=	src/fractol.c src/match.c src/mandelbrot.c src/color.c \
					src/julia.c src/hook.c src/zoom.c src/switch.c

OBJS			= $(SRCS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror
HEADERS			= src/fractol.h
LFLAGS			= -Lmlx -lmlx -framework OpenGL -framework AppKit

NAME			= fractol

all:			$(NAME)

$(NAME):		
				make -C mlx
				$(CC) $(CFLAGS) -c $(SRCS) -I$(HEADERS)
				mv *.o src/
				$(CC) $(CFLAGS) $(LFLAGS) -o $(NAME) $(OBJS)
clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)
