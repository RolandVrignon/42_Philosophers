/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 13:51:44 by rvrignon          #+#    #+#             */
/*   Updated: 2022/08/03 13:52:02 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_args(char **av)
{
	int i;
	int j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while(av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
			{
				ft_printf("One of args is not an int\n");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
