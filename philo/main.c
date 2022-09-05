/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 19:19:29 by vangirov          #+#    #+#             */
/*   Updated: 2022/09/05 20:49:35 by vangirov         ###   ########.fr       */
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
		wisdom->philos[i]->last_meal = ft_usec_now();
		i++;
	}
}

void	ft_join_threads(t_wisdom *wisdom)
{
	int	i;

	i = 0;
	while (i < wisdom->num_ph)
		pthread_join(wisdom->threads[i++], NULL);
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
	}
	else
		return (1);
	return (0);
}
