CC = cc

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft_gnl_printf.a

HEADER = -Iincludes -I$(LIBFT_DIR)

NAME = minishell

SRC_DIR = src/

SRCS =	$(shell find $(SRC_DIR) -name '*.c')

OBJS =	$(SRCS:%.c=$(OBJ_DIR)/%.o)

OBJ_DIR = build

CFLAGS = -Werror -Wall -Wextra -fPIE -g $(HEADER)
READLINE_FLAG = -lreadline

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) -pie -o $@ $(READLINE_FLAG)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

LEAKS := valgrind --leak-check=full --show-leak-kinds=all \
	--track-origins=yes --track-fds=yes \
	--suppressions=$(CURDIR)/valgrind_readline.supp

vl: all
	@printf "Running valgrind (interactive). Valgrind log -> valgrind-out.txt\n"
	@$(LEAKS) ./$(NAME)

clean:
	@make -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re val_leaks

#valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --suppressions=valgrind_readline.supp ./minishell
