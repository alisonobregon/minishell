DEFAULT = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

NAME = minishelll

SRC =	./src/main.c \

SRCB =

OBJ = $(SRC:.c=.o)

OBJB = $(SRCB:.c=.o)

CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address,leak
CC = gcc
#-no-pie

all: $(NAME) show_progress

$(NAME): $(OBJ)
	@make -s -C libft
	$(CC) $(CFLAGS) $(OBJ) -L libft -lft -o $(NAME)

show_progress:
		@for file in $(SRC); do \
			echo "$(GREEN)Compiling $$file "; \
		done; \
		echo "Compiled: 100%$(DEFAULT)"; \

clean:
	rm -f  $(NAME)
	@make clean -s -C libft

fclean: clean
	rm -f  $(OBJ)
	@make clean -s -C libft

re: fclean all


.PHONY: clean fclean re all