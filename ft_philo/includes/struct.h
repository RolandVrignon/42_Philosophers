/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 13:43:26 by rvrignon          #+#    #+#             */
/*   Updated: 2022/08/03 13:56:39 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include "../../libft/libft.h"

typedef struct s_philo
{
	int				id;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				eatsnb;
	struct s_philo	*next;
	struct s_philo	*prev;
}	t_philo;

typedef struct s_philosophers
{
	int		nb;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		eatsnb;
	t_philo	*philo;
}	t_philosophers;

#endif