NAME = minishell
LIBFT_DIR = ./lib/libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBS = -I$(LIBFT_DIR) -I./include
SRC_DIR = ./src

VPATH = $(SRC_DIR) $(SRC_DIR)/execute $(SRC_DIR)/tokens $(SRC_DIR)/utils $(SRC_DIR)/parse $(SRC_DIR)/execute/builtins

SRCS =	main.c \
		run.c exec.c pipex_utils.c \
		parse_cmd.c parse_block.c parse_line.c parse_exec.c parse_pipe.c parse_redir.c \
		cmd_init.c print_ast.c \
		tokenizer.c token_init.c expand.c quote_prompt.c heredoc_prompt.c \
		utils.c ft_split2.c free.c print.c\
		signals.c gbcollec.c builtins.c export.c echo.c unset.c

OBJS_DIR = objects
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
CC = cc
CFLAGS = -Wall -Werror -Wextra $(LIBS)
DEBUG_FLAGS = -Wall -Werror -Wextra -fsanitize=address -g $(LIBS)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(LIBFT_DIR) -lft -lreadline

debug: CFLAGS = $(DEBUG_FLAGS)
debug: re

$(LIBFT):
	make -C $(LIBFT_DIR)

$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	@echo "Creating $(OBJS_DIR) directory"
	@mkdir -p $(OBJS_DIR)

clean:
	rm -rf $(OBJS_DIR)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re debug