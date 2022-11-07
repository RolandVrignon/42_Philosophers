/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 13:51:44 by rvrignon          #+#    #+#             */
/*   Updated: 2022/11/07 17:47:06 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_args(char **av)
{
	int		i;
	int		j;
	char	*cmp;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
			{
				printf("There is either letter in one of args or one arg is negative\n");
				return (0);
			}
			j++;
		}
		cmp = ft_itoa(ft_atoi(av[i]));
		if (ft_strncmp(cmp, av[i], ft_strlen(av[i])) != 0)
		{
			printf("One of args is not an int\n");
			free(cmp);
			return (0);
		}
		free(cmp);
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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		if (s1[i] == '\0')
			return (0);
		i++;
	}
	return (0);
}

static char	*process(int j, int len, char *str, long long int n)
{
	int	i;

	if (!str)
		return (NULL);
	i = len;
	while (len + j > 0)
	{
		str[len + j - 1] = (n % 10 + '0');
		n = n / 10;
		len--;
	}
	if (j == 1)
		str[0] = '-';
	str[i + j] = '\0';
	return (str);
}

char	*ft_itoa(long long int n)
{
	char	*str;
	int		j;
	int		len;
	int		i;

	j = 0;
	if (n < 0)
	{
		n = -n;
		j = 1;
	}
	i = n;
	len = 1;
	while (i >= 10)
	{
		len++;
		i = i / 10;
	}
	str = malloc(sizeof(char) * (len + j + 1));
	if (!str)
		return (NULL);
	return (process(j, len, str, n));
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}