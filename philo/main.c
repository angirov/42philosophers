/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 19:19:29 by vangirov          #+#    #+#             */
/*   Updated: 2022/09/11 20:46:32 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_create_threads(t_wisdom *wisdom)
{
	int	i;

	wisdom->start = ft_usec_now();
	i = 0;
	while (i < wisdom->num_ph)
	{
		pthread_create(wisdom->threads + i, NULL,
			(void *)(&ft_philo_life), wisdom->philos[i]);
		pthread_mutex_lock(&wisdom->philos[i]->mtx_last);
		wisdom->philos[i]->last_meal = ft_usec_now();
		pthread_mutex_unlock(&wisdom->philos[i]->mtx_last);
		i++;
	}
}

void	ft_join_threads(t_wisdom *wisdom)
{
	int	i;

	i = 0;
	while (i < wisdom->num_ph)
		pthread_join(wisdom->threads[i++], NULL);
	pthread_mutex_destroy(&wisdom->mtx_done);
	pthread_mutex_destroy(&wisdom->mtx_death);
	pthread_mutex_destroy(&wisdom->mtx_print);
}

int	main(int argc, char **argv)
{
	t_wisdom	wisdom;
	int			i;

	if (ft_init(argc, argv, &wisdom) == 0)
	{
		ft_create_threads(&wisdom);
		ft_god(&wisdom);
		ft_join_threads(&wisdom);
		ft_free(&wisdom);
	}
	else
		return (1);
	return (0);
}
