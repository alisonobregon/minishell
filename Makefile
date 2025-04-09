DEFAULT	= \033[0;39m
GRAY	= \033[0;90m
RED		= \033[0;91m
GREEN	= \033[0;92m
YELLOW	= \033[0;93m
BLUE	= \033[0;94m
MAGENTA	= \033[0;95m
CYAN	= \033[0;96m
WHITE	= \033[0;97m

NAME	= minishell

SRC	=	./src/minishell.c \
		./src/built-ins/builtins-utils.c \
		./src/built-ins/export.c \
		./src/built-ins/unset.c \
		./src/built-ins/env.c \
		./src/built-ins/exit.c \
		./src/built-ins/cd.c \
		./src/built-ins/echo.c \
		./src/parsing/parsing.c \
		./src/parsing/checker.c \
		./src/parsing/utils_parsing.c \
		./src/parsing/create_command.c \
		./src/parsing/create_command_others.c \
		./src/parsing/outfiles.c \
		./src/parsing/pipes.c \
		./src/utils/utils.c \
		./src/utils/utils2.c \
		./src/exec/exec_utils2.c \
		./src/exec/exec_utils.c \
		./src/exec/exec.c \
		./src/exec/get_path.c \
		./src/exec/redirections.c \
		./src/exec/here_doc.c \
		./src/exec/free_exec.c \
		./src/exec/other_free.c \
		./src/prompt/prompt_utils.c \
		./src/prompt/prompt.c \
		./src/signals/signals.c \
		./src/signals/other_signals.c\
		./src/parsing/quotes.c \
		./src/parsing/utils_quotes.c \
		./src/parsing/env.c \
		./src/prompt/init_text.c \

OBJ	= $(SRC:.c=.o)

INCLUDES = -I/mingw64/include

CFLAGS = -Wall -Werror -Wextra $(INCLUDES) -g3

FLAGS = -L/mingw64/lib -lreadline -lhistory -ltermcap

CC = cc
#-no-pie

all: $(NAME) show_progress

$(NAME): $(OBJ)
	@make -s -C libft
	$(CC) $(OBJ) $(CFLAGS) $(FLAGS) -L libft -lft -o $(NAME)

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

git:
	git add .
	git commit
	git push

.PHONY: clean fclean re all
