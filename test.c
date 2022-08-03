#include "philo.h"

// First exercice

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


// Second exercices - RACE Conditions

int mail = 0;

void* routine()
{
	int i;

	for (i = 0; i < 10000000; i++)
		mail++;
}

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	pthread_t t1, t2;

	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return 1;
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
		return 2;
	if (pthread_join(t1, NULL) != 0)
		return 3;
	if (pthread_join(t2, NULL) != 0)
		return 4;
	ft_printf("Mails = %d", mail);
	return (0);
}
