/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 17:48:03 by rvrignon          #+#    #+#             */
/*   Updated: 2022/08/03 11:55:26 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include "../libft/libft.h"

typedef struct s_philo
{
	int				id;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				eatsnb;
	struct s_philo	*next;
}	t_philo;

typedef struct s_philosophers
{
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		eatsnb;
	t_philo *philo;
}	t_philosophers;

int				usage(void);

int				check_args(char **av);

t_philo			*philo_lstaddback(t_philo *philo, t_philosophers *philos, int i);

t_philo			*create_philos(char **av, t_philosophers *philos);

t_philosophers	*set_data(int ac, char **av);

void			free_philos(t_philosophers *philos);

#endif