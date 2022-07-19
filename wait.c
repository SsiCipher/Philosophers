#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	pid_t	pid;
	int		exit_code;

	pid = fork();
	if (pid == -1)
		printf("Error");
	else if (pid == 0)
	{
		printf("Sleepy child 1\n");
		exit(0);
	}
	pid = fork();
	if (pid == -1)
		printf("Error");
	else if (pid == 0)
	{
		printf("Sleepy child 2\n");
		sleep(2);
		exit(1);
	}
	waitpid(-1, &exit_code, 0);
	printf("Exit code is: %d\n", exit_code);

	return (0);
}
