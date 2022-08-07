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

// pthread_mutex_t mutexFuel;
// pthread_cond_t condFuel;
// int fuel = 0;

// void* fuel_filling(void* arg){
// 	int i = 0;

// 	while (i < 5)
// 	{
// 		pthread_mutex_lock(&mutexFuel);
// 		fuel += 15;
// 		printf("Filling Fuel... %d\n", fuel);
// 		pthread_mutex_unlock(&mutexFuel);
// 		pthread_cond_signal(&condFuel);
// 		sleep(1);
// 	}
// }

// void* car(void *arg)
// {
// 		pthread_mutex_lock(&mutexFuel);
// 		while (fuel < 40)
// 		{
// 			printf("Not enough fuel, i'm waiting...\n");
// 			pthread_cond_wait(&condFuel, &mutexFuel);
// 		}
// 		fuel -= 40;
// 		printf("Got Fuel... Now left %d\n", fuel);
// 		pthread_mutex_unlock(&mutexFuel);
// }	

// int main(int ac, char **av)
// {
// 	int i = 0;
// 	pthread_t th[2];
// 	pthread_mutex_init(&mutexFuel, NULL);
// 	pthread_cond_init(&condFuel, NULL);
// 	while (i++ < 2)
// 	{
// 		if (i == 1)
// 		{
// 			if (pthread_create(&th[i], NULL, &fuel_filling, NULL) != 0)
// 				return 1;
// 		}
// 		else
// 		{
// 			if (pthread_create(&th[i], NULL, &car, NULL) != 0)
// 				return 2;
// 		}
// 	}
// 	i = 0;
// 	while (i++ < 2)
// 	{
// 		if (pthread_join(th[i], NULL) != 0)
// 			return 3;
// 	}
// 	pthread_mutex_destroy(&mutexFuel);
// 	pthread_cond_destroy(&condFuel);
// 	return 0;
// }

// ----------------------- Practical example for pthread_mutex_trylock

pthread_mutex_t stoveMutex[4];
int stoveFuel[4] = {100, 100, 100, 100};

void* routine(void *args)
{
	int i = 0;

	while (i++ < 4)
	{
		if (pthread_mutex_trylock(&stoveMutex[i]) == 0)
		{
			int fuelNeeded  = (rand() % 20);
			if (stoveFuel[i] - fuelNeeded < 0)
				printf("No more fuel, going home\n");
			else {
				stoveFuel[i] -= (rand() % 20);
				usleep(500000);
				printf("fuel left : %d\n", stoveFuel[i]);
			}
			pthread_mutex_unlock(&stoveMutex[i]);
			break;
		}
		else
		{
			if (i == 3)
			{
				printf("No stove available yet, im waiting\n");
				usleep(300000);
				i = 0;
			}
		}
	}
}

int main(int ac, char **av)
{
	srand(time(NULL));
	int			i;
	pthread_t	th[10];
	
	i = 0;
	while(i++ < 4)
		pthread_mutex_init(&stoveMutex[i], NULL);

	i = 0;
	while (i++ < 10)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
			perror("Failed to create mutex");
	}

	i = 0;
	while (i++ < 10)
	{
		if (pthread_join(th[i], NULL) != 0)
			perror("Failed to join mutex");
	}

	i = 0;
	while(i++ < 4)
		pthread_mutex_destroy(&stoveMutex[i]);
}

// -------------------- Pthread_exit

// void* roll_dice()
// {
// 	int value = (rand() % 6) + 1;
// 	int *result = malloc(sizeof(int));
// 	*result = value;
// 	printf("Thread result : %p\n", result);
// 	pthread_exit((void *) result);
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

// ------------- Pthread barrrier

// pthread_barrier_t barrier;

// void* routine(void* args) {
//     while (1) {
//         printf("Waiting at the barrier...\n");
//         sleep(1);
//         pthread_barrier_wait(&barrier);
//         printf("We passed the barrier\n");
//         sleep(1);
//     }
// }

// int main(int argc, char *argv[]) {
// 	pthread_t th[10];
// 	int i;
//     pthread_barrier_init(&barrier, NULL, 10);
// 	for (i = 0; i < 10; i++) {
// 		if (pthread_create(&th[i], NULL, &routine, NULL) != 0) {
// 			perror("Failed to create thread");
// 		}
// 	}
// 	for (i = 0; i < 10; i++) {
// 		if (pthread_join(th[i], NULL) != 0) {
// 			perror("Failed to join thread");
// 		}
// 	}
//     pthread_barrier_destroy(&barrier);
// 	return 0;
// }

// --------------- Example Barrier

int dice_values[8];
int status[8] = { 0 };

pthread_barrier_t barrierRolledDice;
pthread_barrier_t barrierCalculated;

void* roll(void* args) {
    int index = *(int*)args;
    while (1) {
        dice_values[index] = rand() % 32 + 1;
        pthread_barrier_wait(&barrierRolledDice);
        pthread_barrier_wait(&barrierCalculated);
        if (status[index] == 1) {
            printf("(%d rolled %d) I won\n", index, dice_values[index]);
        } else {
            printf("(%d rolled %d) I lost\n", index, dice_values[index]);
        }
    }
    free(args);
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    pthread_t th[8];
    int i;
    pthread_barrier_init(&barrierRolledDice, NULL, 8 + 1);
    pthread_barrier_init(&barrierCalculated, NULL, 8 + 1);
    for (i = 0; i < 8; i++) {
        int* a = malloc(sizeof(int));
        *a = i;
        if (pthread_create(&th[i], NULL, &roll, (void*) a) != 0) {
            perror("Failed to create thread");
        }
    }

    while (1) {
        pthread_barrier_wait(&barrierRolledDice);
        // Calculate winner
        int max = 0;
        for (i = 0; i < 8; i++) {
            if (dice_values[i] > max) {
                max = dice_values[i];
            }
        }

        for (i = 0; i < 8; i++) {
            if (dice_values[i] == max) {
                status[i] = 1;
            } else {
                status[i] = 0;
            }
        }
        sleep(1);
        printf("==== New round starting ====\n");
        pthread_barrier_wait(&barrierCalculated);
    }

    for (i = 0; i < 8; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }
    pthread_barrier_destroy(&barrierRolledDice);
    pthread_barrier_destroy(&barrierCalculated);
    return 0;
}