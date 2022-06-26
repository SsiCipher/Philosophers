COMP	= cc
NAME	= philo_bonus
FLAGS	= -Wall -Wextra -Werror
SRCS	= src/init_data.c src/routine.c src/utils.c 
INCS	= -I includes
LIBS	= -lpthread

all: $(NAME)

$(NAME): $(SRCS) main.c
	$(COMP) $(FLAGS) $(INCS) $(SRCS) $(LIBS) main.c -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all
