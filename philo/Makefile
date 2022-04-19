NAME	= philo
COMP	= cc
FLAGS	= -Wall -Wextra -Werror
INCS	= -I .
SRCS	= src/utils.c main.c

all: $(NAME)

$(NAME):
	$(COMP) $(FLAGS) $(INCS) $(SRCS) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean
