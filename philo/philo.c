/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 00:36:41 by vangirov          #+#    #+#             */
/*   Updated: 2022/09/05 20:48:56 by vangirov         ###   ########.fr       */
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
			&& wisdom->done >= wisdom->num_ph)
			break ;
		pthread_mutex_lock(&wisdom->philos[i]->mtx_last);
		if (ft_usec_now() > wisdom->philos[i]->last_meal + us_to_die)
		{
			wisdom->death = 1;
			diff = (ft_usec_now() - (wisdom->philos[i]->last_meal + us_to_die));
			ft_print_action(wisdom->philos[i], "died", diff / 1000);
			break ;
		}
		pthread_mutex_unlock(&wisdom->philos[i]->mtx_last);
		i = (i + 1) % wisdom->num_ph;
		usleep(100);
	}
	ft_free(wisdom);
	exit(0);
}

void	ft_desync(t_philo *philo, int *fork_right, int *fork_left)
{
	*fork_right = (philo->index + 1) % philo->wisdom->num_ph;
	*fork_left = philo->index;
	if (philo->index % 2)
	{
		usleep(15000 + 1000 * philo->index);
	}
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mtx_last);
	philo->last_meal = ft_usec_now();
	ft_print_action(philo, "is eating", ++philo->times_eaten);
	if (philo->wisdom->num_to_eat > 0
		&& philo->times_eaten >= philo->wisdom->num_to_eat)
		philo->wisdom->done++;
	pthread_mutex_unlock(&philo->mtx_last);
	ft_wait(philo->wisdom->us_to_eat);
}

void	ft_philo_life(t_philo *philo)
{
	int	fork_right;
	int	fork_left;

	ft_desync(philo, &fork_right, &fork_left);
	while (!philo->wisdom->death && (philo->wisdom->num_to_eat < 0
			|| philo->times_eaten < philo->wisdom->num_to_eat))
	{	
		pthread_mutex_lock(philo->wisdom->mtx_forks + fork_right);
		ft_print_action(philo, "has taken a right forkk", fork_right + 1);
		philo->wisdom->forks[fork_right] = 1;
		pthread_mutex_lock(philo->wisdom->mtx_forks + fork_left);
		ft_print_action(philo, "has taken a left  forkk", fork_left + 1);
		philo->wisdom->forks[fork_left] = 1;
		if (!philo->wisdom->death)
			ft_eat(philo);
		pthread_mutex_unlock(philo->wisdom->mtx_forks + fork_right);
		philo->wisdom->forks[fork_right] = 0;
		pthread_mutex_unlock(philo->wisdom->mtx_forks + fork_left);
		philo->wisdom->forks[fork_left] = 0;
		ft_print_action(philo, "is sleeping", -1);
		ft_wait(philo->wisdom->us_to_sleep);
		ft_print_action(philo, "is thinking", -1);
	}
}
