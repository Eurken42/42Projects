# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scorreia <scorreia@student.42lausanne.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/29 16:25:33 by scorreia          #+#    #+#              #
#    Updated: 2022/03/15 19:17:09 by scorreia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
SRCS			=	push_swap.c swap_a.c swap_b.c solve.c solve_v2.c \
					check.c display.c split.c stack_start.c

OBJS			= $(SRCS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror
HEADERS			= push_swap.h

NAME			= push_swap

all:			$(NAME)

$(NAME):		
				$(CC) $(CFLAGS) -c $(SRCS) -I$(HEADERS)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)
