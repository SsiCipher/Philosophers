#include "philo.h"

int	print_error(char *error)
{
	while (*error)
		write(2, error++, 1);
	return (1);
}

int main(int argc, char **argv)
{
	(void)argv;
	if (argc < 5 || argc > 6)
		return (print_error("Error:\nWrong arguments\n"));
	return (0);
}
