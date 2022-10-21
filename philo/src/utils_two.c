/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 13:51:44 by rvrignon          #+#    #+#             */
/*   Updated: 2022/10/21 16:27:58 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_args(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
			{
				printf("One of args is not an int\n");
				return (0);
			}
			j++;
		}
		if (ft_atoi(av[i]) < 1)
		{
			printf("One of args is lower than 1\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

long int	ft_atoi(const char *nptr)
{
	long int	i;
	int			positif;
	long int	nb;

	i = 0;
	nb = 0;
	positif = 1;
	while (nptr[i] <= ' ')
		i++;
	if (nptr[i] == '-')
		positif = positif * -1;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + (nptr[i] - '0');
		i++;
	}
	return (nb * positif);
}

t_philosophers	*get_struct(void)
{
	static t_philosophers	philos;

	return (&philos);
}

time_t	get_tmstmp(void)
{
	time_t			mili;
	t_philosophers	*philos;

	philos = get_struct();
	mili = now() - philos->today;
	return (mili);
}
