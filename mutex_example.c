#include "philo/philo.h"

int n = 1;
pthread_mutex_t mtx;

void *th_routine()
{
	pthread_mutex_lock(&mtx);
	printf("n=%d\n", n);
	n++;
	pthread_mutex_unlock(&mtx);
	return (NULL);
}

int main(int argc, char const *argv[])
{
	pthread_t threads[10];

	pthread_mutex_init(&mtx, NULL);

	for (int i = 0; i < 10; i++)
	{
		pthread_create(&threads[i], NULL, th_routine, NULL);
	}

	for (int i = 0; i < 10; i++)
	{
		pthread_join(threads[i], NULL);
	}

	return (0);
}
