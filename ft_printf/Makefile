NAME := libftprintf.a
HEADER := libftprintf.h
CC := @cc
CFLAGS := -Wall -Wextra -Werror -g
SRC := ft_printf.c\
	utils.c\
	mem_to_str.c\

OBJS := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	@ar rcs $(NAME) $(OBJS)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re