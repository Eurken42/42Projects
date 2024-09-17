# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scorreia <scorreia@student.42lausanne.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/29 16:25:33 by scorreia          #+#    #+#              #
#    Updated: 2022/11/07 17:30:57 by scorreia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME = zombie

SRC			=	main.cpp zombieHorde.cpp zombie.cpp

OBJS		=	$(SRC:.cpp=.o)

COMPILE		=	c++

# -std=c++98 displays an error if an unauthorized function is left in the code
FLAGS		=	-Wall -Wextra -Werror -std=c++98

EXE_NAME	=	-o $(NAME)

EXEC		=	$(NAME)

# ------------------------------------- RULES ---------------------------------
all: $(NAME)

$(NAME): $(OBJS)
	$(COMPILE) $(FLAGS) $(OBJS) $(EXE_NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(EXEC)
	
re:	fclean all

.cpp.o:
	${COMPILE} ${FLAGS} -c $< -o ${<:.cpp=.o}

.PHONY:	all clean fclean re

#OBJS = $(SRCS:.cpp=.o)

#all : $(NAME)

#$(NAME) : $(OBJS) $(SRCS)
#	$(COMPILER) $(CFLAGS) $(OBJS) -o $@

#clean : 
#	rm -f $(OBJS)

#fclean : clean 
#	rm -f $(NAME)

#re : fclean all
