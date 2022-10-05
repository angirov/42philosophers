/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 19:19:29 by vangirov          #+#    #+#             */
/*   Updated: 2022/10/05 12:12:20 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_god(t_wisdom *wisdom)
{
	int		i;
	int64_t	us_to_die;
	int64_t	diff;

	us_to_die = wisdom->us_to_die;
	i = 0;
	while (1)
	{
		if (wisdom->num_to_eat > 0
			&& get_done(wisdom) >= wisdom->num_ph)
			break ;
		pthread_mutex_lock(&wisdom->philos[i]->mtx_last);
		if (ft_usec_now() > wisdom->philos[i]->last_meal + us_to_die)
		{
			diff = (ft_usec_now() - (wisdom->philos[i]->last_meal + us_to_die));
			ft_print_action(wisdom->philos[i], "died", diff / 1000);
			set_death(wisdom, 1);
			pthread_mutex_unlock(&wisdom->philos[i]->mtx_last);
			break ;
		}
		pthread_mutex_unlock(&wisdom->philos[i]->mtx_last);
		i = (i + 1) % wisdom->num_ph;
		usleep(100);
	}
}

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
