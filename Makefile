CC = cc

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libftprintf.a

HEADER = -I $(LIBFT_DIR)

NAME = minishell

SRCS =	src/main.c \
		src/shell_loop.c \
		src/shell_utils.c \
		src/builtins/builtins.c \
		src/builtins/echo.c \
		src/builtins/echo_utils.c\
		src/builtins/cd.c\
		src/builtins/env.c\
		src/builtins/exit.c\
		src/builtins/export.c\
		src/builtins/pwd.c\
		src/builtins/unset.c\

OBJS =	$(SRCS:%.c=$(OBJ_DIR)/%.o)

OBJ_DIR = build

CFLAGS = -Werror -Wall -Wextra
READLINE_FLAG = -lreadline

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) -o $@ $(READLINE_FLAG)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean:
	@make -C $(LIBFT_DIR) fclean
	rm -f $(OBJS) $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re
