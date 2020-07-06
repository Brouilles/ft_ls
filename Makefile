NAME = ft_ls

CC = gcc
FLAGS = -Wall -Wextra -Werror
INC = include
INCLUDES = $(INCLUDE:%.h=$(INC)/%.h)
SRC = src
SRCS =	main.c print.c dir.c flags.c list.c
OBJS = $(SRCS:%.c=$(SRC)/%.o)

.PHONY: libs all clean fclean re export

all: $(NAME)

%.o: %.c $(INCLUDES)
	@echo "\033[38;5;125mcompiling $@\033[0m"
	@$(CC) $(FLAGS) -I $(INC) $(INCLUDE_LIBS) -o $@ -c $<

$(NAME): libs $(OBJS)
	@echo "\033[38;5;207mcompiling $(NAME)\033[0m"
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(COMPILE_LIBS)
	@cp $(NAME) ~/bin

clean:
	@rm -f $(OBJS)