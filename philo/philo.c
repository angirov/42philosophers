/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 00:36:41 by vangirov          #+#    #+#             */
/*   Updated: 2022/08/23 19:21:49 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_god(t_wisdom *wisdom)
{
	int		i;
	int64_t	us_to_die;

	us_to_die = wisdom->us_to_die;
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&wisdom->philos[i]->mtx_last);
		if (ft_usec_now() > wisdom->philos[i]->last_meal + us_to_die)
		{
			wisdom->death = 1;
			break ;
		}
		pthread_mutex_unlock(&wisdom->philos[i]->mtx_last);
		i = (i + 1) % wisdom->num_ph;
		usleep(100);
	}
	ft_print(wisdom->philos[i], "died >>>>>>>>>>>>>>>>>>>>>>>>>>>", 
		(ft_usec_now() - wisdom->philos[i]->last_meal) / 1000);
	// free...
}

void	ft_desync(t_philo *philo, int *fork_right, int *fork_left)
{

	// if (philo->wisdom->num_ph % 2 == 0 && 
	// 	philo->index == philo->wisdom->num_ph - 1)
	// {
	// 	*fork_right = philo->index;
	// 	*fork_left = (philo->index + 1) % philo->wisdom->num_ph;
	// }
	// else
	// {
	*fork_right = (philo->index + 1) % philo->wisdom->num_ph;
	*fork_left = philo->index;
	// }
	if (philo->index %2)
	{
		usleep(15000 + 1000 * philo->index);
	}
}

void	ft_philo_life(t_philo *philo)
{
	int	fork_right;
	int	fork_left;

	ft_desync(philo, &fork_right, &fork_left);
	while (!philo->wisdom->death && philo->times_eaten < philo->wisdom->num_to_eat)
	{	
		pthread_mutex_lock(philo->wisdom->mtx_forks + fork_right);
		ft_print_action(philo, "has taken a right forkk", fork_right);
		pthread_mutex_lock(philo->wisdom->mtx_forks + fork_left);
		ft_print_action(philo, "has taken a left  forkk", fork_left);
		
		
		pthread_mutex_lock(&philo->mtx_last);
		philo->last_meal = ft_usec_now();
		pthread_mutex_unlock(&philo->mtx_last);
		
		ft_print_action(philo, "is eating", -1);
		ft_wait(philo->wisdom->us_to_eat);
		
		pthread_mutex_unlock(philo->wisdom->mtx_forks + fork_right);
		pthread_mutex_unlock(philo->wisdom->mtx_forks + fork_left);
		philo->times_eaten++; /////////////////////// or should thye break here???
		ft_print_action(philo, "is sleeping", -1);
		ft_wait(philo->wisdom->us_to_sleep);

		ft_print_action(philo, "is thinking", -1);
	}
}
