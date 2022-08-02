/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 17:48:03 by rvrignon          #+#    #+#             */
/*   Updated: 2022/08/02 19:14:03 by rvrignon         ###   ########.fr       */
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
	int	id;
	int time_die;
	int time_eat;
	int time_sleep;
	int eatsnb;
}	t_philo;

typedef struct s_philosophers
{
	int		time_die;
	int		time_eat;
	int		time_sleep;
	t_philo *philo;
	t_philo *next;
}	t_philosophers;

#endif