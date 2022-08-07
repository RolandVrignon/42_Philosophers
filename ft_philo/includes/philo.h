/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 13:57:03 by rvrignon          #+#    #+#             */
/*   Updated: 2022/08/07 18:22:33 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "struct.h"

int		        usage(void);

void*           routine(void* args);

void            thread_process(t_philosophers *philos);

t_philo	        *philo_lstaddback(t_philo *phil, t_philosophers *philos, int i);

t_philo	        *philo_addlast(t_philo *philo, t_philosophers *philos, int i);

t_philo	        *create_philos(char **av, t_philosophers *philos);

t_philosophers* set_data(int ac, char **av);

void	        free_philos(t_philosophers *philos);

int		        check_args(char **av);

long int        ft_atoi(const char *nptr);

int	            ft_isdigit(int c);

#endif

