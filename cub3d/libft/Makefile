CC 			= gcc

CFLAGS 		= -Wall -Werror -Wextra
INCLUDES	= -I.

OBJS_DIR	= .
SRCS_DIR 	= .

SRCS_NAME	= ft_ctype_0.c ft_ctype_1.c ft_lcs.c ft_mem.c ft_print.c ft_std.c ft_string_0.c ft_string_1.c ft_string_2.c ft_string_3.c ft_striter.c ft_list_0.c ft_list_1.c ft_dblst_0.c ft_dblst_1.c ft_stack_0.c ft_stack_1.c ft_sort.c get_next_line.c get_next_line_utils.c ft_dblst_2.c
SRCS		:= $(patsubst %.c, $(SRCS_DIR)/%.c, $(SRCS_NAME))
OBJS 		:= $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))

PRINTF_DIR	= printf
PRINTF_NAME	= ft_printf.c ft_conv.c ft_tag.c ft_utils.c ft_flags.c ft_parsing.c
PRINTF_OBJS	:= $(patsubst %.c, $(PRINTF_DIR)/bin/%.o, $(PRINTF_NAME))

NAME		= libft.a

#-------------------------------------------------------------------------------------------------#


all:				$(NAME)

$(NAME):			$(OBJS) $(PRINTF_OBJS)
					ar rc $(NAME) $(OBJS) $(PRINTF_OBJS)
					ranlib $(NAME)

#-------------------------------------------------------------------------------------------------#

$(PRINTF_DIR)/bin/%.o:	$(PRINTF_DIR)/srcs/%.c
						make -C $(PRINTF_DIR) $(subst $(PRINTF_DIR)/,,$@)

$(OBJS_DIR)/%.o:		$(SRCS_DIR)/%.c
						$(CC) $(CFLAGS) $(INCLUDES) -o $@ $< -c

#-------------------------------------------------------------------------------------------------#

re:					fclean all

clean:
					make -C $(PRINTF_DIR) clean
					$(RM) $(OBJS) $(BONUS_OBJS) bonus

fclean:				clean
					make -C $(PRINTF_DIR) fclean
					$(RM) $(NAME)

.PHONY:				all clean fclean re
