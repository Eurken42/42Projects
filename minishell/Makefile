OBJS_DIR	= bin
SRCS_DIR 	= srcs
INCL_DIR	= includes
LIBFT_DIR	= libft

CC 			= gcc

CFLAGS 		= -Wall -Werror -Wextra
INCLUDES	= -I$(INCL_DIR) -I$(LIBFT_DIR)
LIBS		= -L$(LIBFT_DIR) -lft -L$(HOME)/.brew/opt/readline/lib -lreadline \
			  -I$(HOME)/.brew/opt/readline/include
LIBFT		= $(LIBFT_DIR)/libft.a

HEAD_NAME	= minishell.h
HEADERS		:= $(patsubst %.h, $(INCL_DIR)/%.h, $(HEAD_NAME))

SRCS_NAME	= minishell.c minishell_utils.c cmd.c env.c instruction.c parsing.c \
			  parsing_utils.c parse_token.c parse_cmd.c parse_inst.c prompt.c \
			  utils.c cd.c pwd.c echo.c exit.c free_destroy.c exec.c \
			  exec_utils.c env_utils.c pipe.c export.c unset.c utils_2.c

SRCS		:= $(patsubst %.c, $(SRCS_DIR)/%.c, $(SRCS_NAME))
OBJS 		:= $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))
B_SRCS_NAME	= 
B_SRCS		:= $(patsubst %.c, $(SRCS_DIR)/%.c, $(B_SRCS_NAME))
B_OBJS 		:= $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(B_SRCS))

NAME		= minishell

#-------------------------------------------------------------------------------------------------#


all:				update $(NAME)

$(NAME):			$(OBJS)
					$(CC) $(CFLAGS) $(LIBS) -o $(NAME) $(OBJS)

update:				
					@make -sC $(LIBFT_DIR)

$(B_NAME):			$(B_OBJS)
					$(CC) $(CFLAGS) $(LIBS) -o $(B_NAME) $(B_OBJS)

#-------------------------------------------------------------------------------------------------#

$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%.c $(LIBFT) $(HEADERS) | bin
					$(CC) $(CFLAGS) $(INCLUDES) -o $@ $< -c

bin:				
					mkdir -p $@

#-------------------------------------------------------------------------------------------------#

re:					fclean all

clean:
					@make -sC $(LIBFT_DIR) clean
					@echo "cleaned libft"
					$(RM) $(OBJS) $(B_OBJS)

fclean:				clean
					@make -sC $(LIBFT_DIR) fclean
					@echo "fcleaned libft"
					$(RM) $(NAME) $(B_NAME)

.PHONY:				all clean fclean re update
