NAME = philo

CC = gcc
FL = -Wall -Wextra -Werror


HEADER = philosophers.h
SRCS =	philosophers.c utils.c make_threads.c sleep_and_eat.c death_checker.c
OBJS = $(SRCS:.c=.o)

.c.o:
	$(CC) $(FL) -o $@ -c $^

all: $(NAME)

$(NAME): $(OBJS) $(HEADER) Makefile
	$(CC) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean:
	rm -f $(OBJS)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
