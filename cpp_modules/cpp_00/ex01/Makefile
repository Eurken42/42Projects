# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scorreia <scorreia@student.42lausanne.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/29 16:25:33 by scorreia          #+#    #+#              #
#    Updated: 2022/11/04 14:29:14 by scorreia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME = phonebook

COMPILER = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98

SRCS			= main.cpp phonebook.cpp contact.cpp
HEADERS			= Phonebook.class.hpp Contact.class.hpp

OBJS = $(SRCS:.cpp=.o)

all : $(NAME)

$(NAME) : $(OBJS) $(SRCS)
	$(COMPILER) $(CFLAGS) $(OBJS) -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all
