# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <time.h>
# include <errno.h>

// -------------------  First exercice

// void* routine()
// {
// 	ft_printf("Test from thread\n");
// 	sleep(3);
// 	ft_printf("Ending thread\n");
// }

// int main(int ac, char **av)
// {
// 	(void)ac;
// 	(void)av;
// 	pthread_t t1, t2;

// 	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
// 		return 1;
// 	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
// 		return 2;
// 	if (pthread_join(t1, NULL) != 0)
// 		return 3;
// 	if (pthread_join(t2, NULL) != 0)
// 		return 4;
// 	return (0);
// }


// ------------------------- Second exercices - RACE Conditions

// int mail = 0;

// void* routine()
// {
// 	int i;

// 	for (i = 0; i < 10000000; i++)
// 		mail++;
// }

// int main(int ac, char **av)
// {
// 	(void)ac;
// 	(void)av;
// 	pthread_t t1, t2;

// 	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
// 		return 1;
// 	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
// 		return 2;
// 	if (pthread_join(t1, NULL) != 0)
// 		return 3;
// 	if (pthread_join(t2, NULL) != 0)
// 		return 4;
// 	ft_printf("Mails = %d", mail);
// 	return (0);
// }

// --------------------------- MUTEXX

// int mail = 0;
// pthread_mutex_t mutex;

// void* routine()
// {
// 	int i;

// 	for (i = 0; i < 10000000; i++)
// 	{
// 		pthread_mutex_lock(&mutex);
// 		mail++;
// 		pthread_mutex_unlock(&mutex);
// 	}
// }

// int main(int ac, char **av)
// {
// 	(void)ac;
// 	(void)av;
// 	pthread_t t1, t2;
// 	pthread_mutex_init(&mutex, NULL);

// 	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
// 		return 1;
// 	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
// 		return 2;
// 	if (pthread_join(t1, NULL) != 0)
// 		return 3;
// 	if (pthread_join(t2, NULL) != 0)
// 		return 4;
// 	pthread_mutex_destroy(&mutex);
// 	printf("Mails = %d", mail);
// 	return (0);
// }

// ------------------------------ CREATE Threads in a loop

// int mail = 0;
// pthread_mutex_t mutex;

// void* routine()
// {
// 	int i;

// 	for (i = 0; i < 10000000; i++)
// 	{
// 		pthread_mutex_lock(&mutex);
// 		mail++;
// 		pthread_mutex_unlock(&mutex);
// 	}
// }

// int main(int ac, char **av)
// {
// 	(void)ac;
// 	(void)av;
// 	int		i;
// 	pthread_t th[16];
// 	pthread_mutex_init(&mutex, NULL);
// 	for (i = 0; i < 16; i++)
// 	{
// 		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
// 		{
// 			perror("Failed to create thread");
// 			return (1);
// 		}
// 		printf("Thread %d has started\n", i);
// 	}
// 	for (i = -0; i < 16; i++)
// 	{
// 		if (pthread_join(th[i], NULL) != 0)
// 			return 2;
// 		printf("Thread %d has finish execution\n", i);
// 	}
// 	pthread_mutex_destroy(&mutex);
// 	printf("Mails = %d", mail);
// 	return (0);
// }

// -------------------- Get a return value from a thread

// void* roll_dice()
// {
// 	int value = (rand() % 6) + 1;
// 	int *result = malloc(sizeof(int));
// 	*result = value;
// 	printf("Thread result : %p\n", result);
// 	return ((void *) result);
// }

// int	main(int ac, char **av)
// {
// 	int *res[4];
// 	srand(time(NULL));
// 	pthread_t th[4];
// 	int i;

// 	for (i = 0; i < 4; i++)
// 	{
// 		if (pthread_create(&th[i], NULL, &roll_dice, NULL) != 0)
// 		{
// 			perror("Failed to create thread");
// 			return (1);
// 		}
// 		printf("Thread %d has started\n", i);
// 	}
// 	for (i = 0; i < 4; i++)
// 	{
// 		if (pthread_join(th[i], (void **) &res[i]) != 0)
// 			return 2;
// 		printf("Thread %d has finish execution\n", i);
// 	}
// 	for (i = 0; i < 4; i++)
// 	{
// 		printf("Result : %d, adress : %p\n", *res[i], res[i]);
// 		free(res[i]);
// 	}
// 	return 0;
// }

// ------------------------- How to pass args to threads

// int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

// void *routine(void *arg)
// {
// 	int index = *(int*)arg;
// 	printf("%d\n", primes[index]);
// 	free(arg);
// }

// int main(int ac, char **av)
// {
// 	pthread_t th[10];
// 	for (int i = 0; i < 10; i++)
// 	{
// 		int* a = malloc(sizeof(int));
// 		*a = i;
// 		if (pthread_create(&th[i], NULL, &routine, a) != 0)
// 			return 1;
// 	}
// 	for (int i = 0; i < 10; i++)
// 	{
// 		if (pthread_join(th[i], NULL) != 0)
// 			return 2;
// 	}
// 	return (0);
// }

// ----------- Sum an array using threads 

// int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

// void* routine(void* arg)
// {
// 	int index = *(int*)arg;
// 	int sum = 0;
// 	for (int i = 0; i < 5; i++)
// 		sum += primes[index + i];
// 	printf("Local Sum = %d\n", sum);
// 	*(int *)arg = sum;
// 	return arg;
// }
// int globalsum = 0;
// int main(int ac, char **av)
// {
// 	pthread_t th[2];
// 	for (int i = 0; i < 2; i++)
// 	{
// 		int* a = malloc(sizeof(int));
// 		*a = i * 5;
// 		if (pthread_create(&th[i], NULL, &routine, a) != 0)
// 			return 1;
// 	}
// 	for (int i = 0; i < 2; i++)
// 	{
// 		int* res;
// 		if (pthread_join(th[i], (void **) &res) != 0)
// 			return 2;
// 		globalsum += *res;
// 		free(res);
// 	}
// 	printf("Globalsum = %d", globalsum);
// 	return (0);
// }

// ----------------- Try Lock (watch if its locked but dont wait)

// pthread_mutex_t	mutex;

// void* routine(void* arg)
// {
// 	if (pthread_mutex_trylock(&mutex) == 0)
// 	{
// 		printf("Got locked\n");
// 		sleep(2);
// 		pthread_mutex_unlock(&mutex);
// 	}
// 	else{
// 		printf("Didn't get locked\n");
// 	}
// }

// int main(int ac, char **av)
// {
// 	pthread_t th[4];
// 	pthread_mutex_init(&mutex, NULL);
// 	for (int i = 0; i < 4; i++)
// 	{
// 		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
// 			return 1;
// 	}
// 	for (int i = 0; i < 4; i++)
// 	{
// 		if (pthread_join(th[i], NULL) != 0)
// 			return 2;
// 	}
// 	return (0);
// }

// -------------------- COnditions variables

pthread_mutex_t mutexFuel;
pthread_cond_t condFuel;
int fuel = 0;

void* fuel_filling(void* arg){
	int i = 0;

	while (i < 5)
	{
		pthread_mutex_lock(&mutexFuel);
		fuel += 15;
		printf("Filling Fuel... %d\n", fuel);
		pthread_mutex_unlock(&mutexFuel);
		pthread_cond_signal(&condFuel);
		sleep(1);
	}
}

void* car(void *arg)
{
		pthread_mutex_lock(&mutexFuel);
		while (fuel < 40)
		{
			printf("Not enough fuel, i'm waiting...\n");
			pthread_cond_wait(&condFuel, &mutexFuel);
		}
		fuel -= 40;
		printf("Got Fuel... Now left %d\n", fuel);
		pthread_mutex_unlock(&mutexFuel);
}	

int main(int ac, char **av)
{
	int i = 0;
	pthread_t th[2];
	pthread_mutex_init(&mutexFuel, NULL);
	pthread_cond_init(&condFuel, NULL);
	while (i++ < 2)
	{
		if (i == 1)
		{
			if (pthread_create(&th[i], NULL, &fuel_filling, NULL) != 0)
				return 1;
		}
		else
		{
			if (pthread_create(&th[i], NULL, &car, NULL) != 0)
				return 2;
		}
	}
	i = 0;
	while (i++ < 2)
	{
		if (pthread_join(th[i], NULL) != 0)
			return 3;
	}
	pthread_mutex_destroy(&mutexFuel);
	pthread_cond_destroy(&condFuel);
	return 0;
}
