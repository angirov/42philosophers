/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 20:40:51 by vangirov          #+#    #+#             */
/*   Updated: 2022/09/04 22:20:27 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s)
	{
		len++;
		s++;
	}
	return (len);
}

int	ft_is_good_num(char *str)
{
	long	n;

	n = 0;
	while (str[n])
	{
		if (ft_strlen(str) > 1 && n == 0 && str[0] == '-')
			n++;
		else if (!ft_isdigit(str[n++]))
			return (0);
	}
	n = ft_atol(str);
	if (n > INT_MAX || n < INT_MIN)
		return (0);
	if (n < 0)
		return (0);
	return (1);
}

int	ft_is_format(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (0);
	i = 1;
	while (argv[i])
	{
		if (!ft_is_good_num(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_set_params(int argc, char **argv, t_wisdom *wisdom)
{
	wisdom->death = 0;
	wisdom->num_ph = ft_atoi(argv[1]);
	wisdom->us_to_die = ft_atoi(argv[2]) * 1000;
	wisdom->us_to_eat = ft_atoi(argv[3])* 1000;
	wisdom->us_to_sleep = ft_atoi(argv[4])* 1000;
	if (argc == 6)
		wisdom->num_to_eat = ft_atoi(argv[5]);
	else
		wisdom->num_to_eat = -1;
}

int	ft_init(int argc, char **argv, t_wisdom *wisdom)
{
	int	i;

	if (!ft_is_format(argc, argv))
	{
		printf("Bad imput: usage: philo number_of_philosophers ");
		printf("ms_to_die ms_to_eat ms_to_sleep ");
		printf("[number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	ft_set_params(argc, argv, wisdom);
	wisdom->forks = malloc(sizeof(int) * wisdom->num_ph);
	wisdom->philos = malloc(sizeof(t_philo *) * wisdom->num_ph);
	wisdom->threads = malloc(sizeof(pthread_t) * wisdom->num_ph);
	pthread_mutex_init(&wisdom->mtx_print, NULL);

	wisdom->mtx_forks = malloc(sizeof(pthread_mutex_t) * wisdom->num_ph);
	i = 0;
	while (i < wisdom->num_ph)
	{
		wisdom->philos[i] = malloc(sizeof(t_philo));
		wisdom->philos[i]->wisdom = wisdom;
		wisdom->philos[i]->index = i;
		wisdom->philos[i]->number = i + 1;
		wisdom->forks[i] = 0;
		pthread_mutex_init(&wisdom->mtx_forks[i], NULL);
		pthread_mutex_init(&wisdom->philos[i]->mtx_last, NULL);
		i++;
	}
	return (0);
}
