/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 13:43:26 by rvrignon          #+#    #+#             */
/*   Updated: 2022/08/09 13:19:09 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t				th;
	pthread_mutex_t			fork_mutex;
	int						id;
	int						is_dead;
	__useconds_t			gotfork_ms;
	int						is_eating;
	__useconds_t			gotsleep_ms;
	int						is_sleeping;
	__useconds_t			start_thinking_ms;
	int						is_thinking;
	int						eatsnb;
	struct s_philo			*next;
	struct s_philo			*prev;
	struct s_philosophers	*philos;
}	t_philo;

typedef struct s_philosophers
{
	int				nb;
	int				time_die_ms;
	int				time_eat_ms;
	int				time_sleep_ms;
	int				eatsnb;
	time_t			today;
	pthread_mutex_t	printf_mutex;
	t_philo			*philo;
}	t_philosophers;

#endif