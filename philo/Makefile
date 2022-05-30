COMP	= cc
NAME	= philo
FLAGS	= -Wall -Wextra -Werror
SRCS	= src/utils.c src/init_data.c src/routine.c
INCS	= -I .
LIBS	= -lpthread

all: $(NAME)

$(NAME): $(SRCS) main.c
	$(COMP) $(FLAGS) $(INCS) $(SRCS) $(LIBS) main.c -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all
