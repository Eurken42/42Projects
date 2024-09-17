OBJS_DIR	= bin
SRCS_DIR 	= srcs
LIBFT_DIR	= ..

CC 			= gcc

CFLAGS 		= -Wall -Werror -Wextra
INCLUDES	= -I./includes -I$(LIBFT_DIR)
LIBS		= -L$(LIBFT_DIR) -lft

SRCS_NAME	= ft_printf.c ft_conv.c ft_tag.c ft_utils.c ft_flags.c ft_parsing.c
SRCS		:= $(patsubst %.c, $(SRCS_DIR)/%.c, $(SRCS_NAME))
OBJS 		:= $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))

LIBFT_OBJS	= $(wildcard $(LIBFT_DIR)/*.o)

NAME		= libftprintf.a
LIBFT		= $(LIBFT_DIR)/libft.a

#-------------------------------------------------------------------------------------------------#


all:				$(NAME)

$(NAME):			$(LIBFT) $(OBJS)
					ar rc $(NAME) $(OBJS) $(LIBFT_OBJS)
					ranlib $(NAME)

compile:			$(OBJS)
					@touch printf

$(LIBFT):
					make -C $(LIBFT_DIR)

#-------------------------------------------------------------------------------------------------#

$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%.c | bin
					$(CC) $(CFLAGS) $(INCLUDES) -o $@ $< -c

%.o:				%.c
					$(CC) $(CFLAGS) $(INCLUDES) -o $@ $< -c

bin:				
					mkdir -p $@

#-------------------------------------------------------------------------------------------------#

re:					fclean all

clean:
					$(RM) $(OBJS) printf

fclean:				clean
					$(RM) $(NAME)

.PHONY:				all clean fclean re
