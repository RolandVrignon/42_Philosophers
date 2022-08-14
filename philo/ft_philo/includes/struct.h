/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 13:43:26 by rvrignon          #+#    #+#             */
/*   Updated: 2022/08/15 00:49:33 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef enum e_status {
	think,
	ready_to_fork,
	ready_to_eat,
	eat,
	sleeps,
	died,
	done,
	start,
}	t_status;

typedef struct s_philo
{
	pthread_t				th;
	pthread_mutex_t			fork_mutex;
	pthread_mutex_t			status_mutex;
	int						id;
	int						is_dead;
	int						eatsnb;
	t_status				status;
	__useconds_t			gotfork_ms;
	__useconds_t			gotsleep_ms;
	__useconds_t			start_thinking_ms;
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
	int				finish;
	time_t			today;
	t_philo			*philo;
}	t_philosophers;

#endif