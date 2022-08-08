/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 13:43:26 by rvrignon          #+#    #+#             */
/*   Updated: 2022/08/08 17:18:17 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct  s_timeval  {
  	time_t				tv_sec ;
	suseconds_t			tv_usec ;
}	t_timeval;

typedef struct s_philo
{
	pthread_t				th;
	pthread_mutex_t 		forkMutex;
	int						id;
	__useconds_t			time_die;
	__useconds_t			time_eat;
	__useconds_t			time_sleep;
	__useconds_t			gotfork;
	__useconds_t			gotsleep;
	int						eatsnb;
	struct s_philo			*next;
	struct s_philo			*prev;
	struct s_philosophers 	*philos;
}	t_philo;

typedef struct s_philosophers
{
	int				nb;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				eatsnb;
	time_t			today;
	pthread_mutex_t	printfMutex;
	t_philo			*philo;
}	t_philosophers;

#endif