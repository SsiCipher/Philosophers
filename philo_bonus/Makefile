COMP	= cc
NAME	= philo_bonus
FLAGS	= -Wall -Wextra -Werror
INCS	= -I includes
SRCS	= src/init_data_bonus.c src/routine_bonus.c src/utils_bonus.c
LIBS	= -lpthread

all: $(NAME)

$(NAME): $(SRCS) includes/philo_bonus.h main_bonus.c
	$(COMP) $(FLAGS) $(INCS) $(SRCS) $(LIBS) main_bonus.c -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all
