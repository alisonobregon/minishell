# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gongarci <gongarci@student.42madrid>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/26 10:23:11 by gongarci          #+#    #+#              #
#    Updated: 2023/09/26 10:23:15 by gongarci         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Color Aliases
DEFAULT = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

SRC =	./strings/ft_atoi.c \
		./strings/ft_empty.c \
		./strings/ft_itoa.c \
		./strings/ft_strchr.c \
		./strings/ft_strlen.c \
		./strings/ft_strrchr.c \
		./strings/ft_strlcpy.c \
		./strings/ft_strncmp.c \
		./strings/ft_strnstr.c \
		./strings/ft_strlcat.c \
		./strings/ft_strdup.c \
		./strings/ft_substr.c \
		./strings/ft_strjoin.c \
		./strings/ft_strtrim.c \
		./strings/ft_split.c \
		./strings/ft_strmapi.c \
		./strings/ft_striteri.c \
		./ft_is/ft_int_max.c \
		./ft_is/ft_isalpha.c \
		./ft_is/ft_isdigit.c \
		./ft_is/ft_isalnum.c \
		./ft_is/ft_isascii.c \
		./ft_is/ft_isprint.c \
		./ft_is/ft_toupper.c \
		./ft_is/ft_tolower.c \
		./ft_is/ft_blank.c \
		./memory/ft_bzero.c \
		./memory/ft_memcpy.c \
		./memory/ft_memset.c \
		./memory/ft_memmove.c \
		./memory/ft_memcmp.c \
		./memory/ft_memchr.c \
		./memory/ft_calloc.c \
		./put/ft_putchar_fd.c \
		./put/ft_putstr_fd.c \
		./put/ft_putendl_fd.c \
		./put/ft_putnbr_fd.c \
		./list/ft_lstnew.c \
		./list/ft_lstadd_front.c \
		./list/ft_lstsize.c \
		./list/ft_lstlast.c \
		./list/ft_lstadd_back.c \
		./list/ft_lstdelone.c \
		./list/ft_lstclear.c \
		./list/ft_lstiter.c \
		./list/ft_lstmap.c \
		./printf/ft_putnbr.c \
		./printf/ft_printf.c \
		./printf/ft_putchar.c \
		./printf/ft_puthexa.c \
		./printf/ft_putmem.c \
		./printf/ft_string.c \
		./printf/ft_unprintf.c \
		./printf/ft_unsigned_int.c \
		./gnl/get_next_line_utils.c \
		./gnl/get_next_line.c \

OBJS = $(SRC:.c=.o)
CURRENT_FILE = 1
TOTAL_FILES = $(words $(SRC))
COMPILER = gcc
CFLAGS = -Wall -Wextra -Werror

NAME = libft.a



all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

%.o: %.c
	@printf "\033[KCompiling $<... $(shell echo $$(($(CURRENT_FILE) * 100 / $(TOTAL_FILES))))%%\r"
	@$(COMPILER) $(CFLAGS) -c $< -o $@
	$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE) + 1))))
	
#bonus: $(OBJS_BONUS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all 

#BONUS = ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c \
#bonus
#OBJS_BONUS = $(BONUS:.c=.o)
#	ar rc $(NAME) $(OBJS_BONUS)
#	rm -f $(OBJS_BONUS)