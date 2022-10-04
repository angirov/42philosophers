/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 00:36:41 by vangirov          #+#    #+#             */
/*   Updated: 2022/10/04 16:28:29 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_desync(t_philo *philo, int *fork_right, int *fork_left)
{
	*fork_right = (philo->index + 1) % philo->wisdom->num_ph;
	*fork_left = philo->index;
	if (philo->index % 2)
	{
		ft_wait(100000);
	}
}

int	get_eaten(t_philo *philo)
{
	int	eaten;

	pthread_mutex_lock(&philo->mtx_last);
	eaten = philo->times_eaten;
	pthread_mutex_unlock(&philo->mtx_last);
	return (eaten);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mtx_last);
	philo->last_meal = ft_usec_now();
	philo->times_eaten++;
	ft_print_action(philo, "is eating", philo->times_eaten);
	pthread_mutex_unlock(&philo->mtx_last);
	pthread_mutex_lock(&philo->wisdom->mtx_done);
	if (philo->wisdom->num_to_eat > 0
		&& philo->times_eaten >= philo->wisdom->num_to_eat)
		philo->wisdom->done++;
	pthread_mutex_unlock(&philo->wisdom->mtx_done);
	ft_wait(philo->wisdom->us_to_eat);
}

int	ft_take_forks(t_philo *philo, int fork_right, int fork_left)
{
	pthread_mutex_lock(philo->wisdom->mtx_forks + fork_right);
	ft_print_action(philo, "has taken a right fork", fork_right + 1);
	philo->wisdom->forks[fork_right] = 1;
	if (fork_right == fork_left)
		return (0);
	pthread_mutex_lock(philo->wisdom->mtx_forks + fork_left);
	ft_print_action(philo, "has taken a left  fork", fork_left + 1);
	philo->wisdom->forks[fork_left] = 1;
	return (1);
}

void	ft_philo_life(t_philo *philo)
{
	int	fork_right;
	int	fork_left;
	int	eaten;

	ft_desync(philo, &fork_right, &fork_left);
	while (!get_death(philo->wisdom) && (philo->wisdom->num_to_eat < 0
			|| get_eaten(philo) < philo->wisdom->num_to_eat))
	{
		if (!ft_take_forks(philo, fork_right, fork_left))
			break ;
		if (!get_death(philo->wisdom))
			ft_eat(philo);
		philo->wisdom->forks[fork_right] = 0;
		pthread_mutex_unlock(philo->wisdom->mtx_forks + fork_right);
		philo->wisdom->forks[fork_left] = 0;
		pthread_mutex_unlock(philo->wisdom->mtx_forks + fork_left);
		ft_print_action(philo, "is sleeping", -1);
		ft_wait(philo->wisdom->us_to_sleep);
		ft_print_action(philo, "is thinking", -1);
	}
}
