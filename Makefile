NAME	= philo
COMP	= cc
FLAGS	= -Wall -Wextra -Werror
INCS	= -I .
LIBS	= -lpthread
SRCS	= src/utils.c src/init_data.c src/routine.c main.c

all: $(NAME)

$(NAME):
	$(COMP) $(FLAGS) $(INCS) $(SRCS) $(LIBS) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all
