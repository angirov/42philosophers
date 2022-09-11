/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 20:40:51 by vangirov          #+#    #+#             */
/*   Updated: 2022/09/11 19:57:29 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_set_params(int argc, char **argv, t_wisdom *wisdom)
{
	wisdom->death = 0;
	wisdom->num_ph = ft_atoi(argv[1]);
	wisdom->us_to_die = ft_atoi(argv[2]) * 1000;
	wisdom->us_to_eat = ft_atoi(argv[3]) * 1000;
	wisdom->us_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
		wisdom->num_to_eat = ft_atoi(argv[5]);
	else
		wisdom->num_to_eat = -1;
}

void	ft_loop_philos(t_wisdom *wisdom)
{
	int	i;

	i = 0;
	while (i < wisdom->num_ph)
	{
		wisdom->philos[i] = malloc(sizeof(t_philo));
		wisdom->philos[i]->wisdom = wisdom;
		wisdom->philos[i]->index = i;
		wisdom->philos[i]->number = i + 1;
		wisdom->philos[i]->times_eaten = 0;
		wisdom->forks[i] = 0;
		pthread_mutex_init(&wisdom->mtx_forks[i], NULL);
		pthread_mutex_init(&wisdom->philos[i]->mtx_last, NULL);
		i++;
	}
}

int	ft_init(int argc, char **argv, t_wisdom *wisdom)
{
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
	pthread_mutex_init(&wisdom->mtx_done, NULL);
	pthread_mutex_init(&wisdom->mtx_death, NULL);
	pthread_mutex_init(&wisdom->mtx_print, NULL);
	wisdom->done = 0;
	wisdom->mtx_forks = malloc(sizeof(pthread_mutex_t) * wisdom->num_ph);
	ft_loop_philos(wisdom);
	return (0);
}

int	ft_free(t_wisdom *wisdom)
{
	int	i;

	i = 0;
	while (i < wisdom->num_ph)
	{
		free(wisdom->philos[i]);
		i++;
	}
	free(wisdom->mtx_forks);
	free(wisdom->forks);
	free(wisdom->philos);
	free(wisdom->threads);
	return (0);
}
