OBJS_DIR	= bin
SRCS_DIR 	= srcs
INCL_DIR	= includes
LIBFT_DIR	= libft
MLX_DIR		= mlx

CC 			= gcc

ifeq ($(shell uname), Linux)
MLX_DIR		= mlx-linux
endif

CFLAGS 		= -Wall -Werror -Wextra
INCLUDES	= -I$(INCL_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)
LIBS		= -L$(LIBFT_DIR) -L$(MLX_DIR) -lft -Lmlx -lmlx -framework OpenGL -framework AppKit
LIBFT		= $(LIBFT_DIR)/libft.a

HEAD_NAME	= cub3d.h
HEADERS		:= $(patsubst %.h, $(INCL_DIR)/%.h, $(HEAD_NAME))

SRCS_NAME	= main.c parse_args.c parse_map.c detection.c utils.c utils_parsing.c \
			  utils_parsing_2.c utils_parsing_3.c create.c create_2.c create_utils.c \
			  free_exit.c hook.c hook_loop.c draw.c draw_utils.c draw_column.c draw_column_utils.c \
			  ray_casting.c ray_utils.c ray_utils_2.c

SRCS		:= $(patsubst %.c, $(SRCS_DIR)/%.c, $(SRCS_NAME))
OBJS 		:= $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))
B_SRCS_NAME	= 
B_SRCS		:= $(patsubst %.c, $(SRCS_DIR)/%.c, $(B_SRCS_NAME))
B_OBJS 		:= $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(B_SRCS))

NAME		= cub3D

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
