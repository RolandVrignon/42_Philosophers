#ifndef PHILO_H
# define PHILO_H

# include "struct.h"

int				usage(void);

int				check_args(char **av);

t_philo			*philo_lstaddback(t_philo *philo, t_philosophers *philos, int i);

t_philo			*philo_addlast(t_philo *philo, t_philosophers *philos, int i);

t_philo			*create_philos(char **av, t_philosophers *philos);

t_philosophers 	*set_data(int ac, char **av);

void			free_philos(t_philosophers *philos);

#endif
