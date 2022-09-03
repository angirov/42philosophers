/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 19:19:29 by vangirov          #+#    #+#             */
/*   Updated: 2022/08/23 19:19:29 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_philo_liffe(t_philo *philo)
{
	printf("HHHHHHHHHHHHHHHHHH\n");

	int	fork_right;
	int	fork_left;
	long	us_to_eat;
	long	us_to_sleep;

	us_to_eat = philo->wisdom->us_to_eat;
	us_to_sleep = philo->wisdom->us_to_sleep;
	if (philo->index == philo->wisdom->num_ph - 1)
	{
		fork_left = (philo->index + 1) % philo->wisdom->num_ph;
		fork_right = philo->index;
	}
	else
	{
		fork_left = philo->index;
		fork_right = (philo->index + 1) % philo->wisdom->num_ph;
	}
	if (philo->index %2 == 0)
		usleep(15000);
	ft_print(philo, "num to eat:", philo->wisdom->num_to_eat);
	while (!philo->wisdom->death && philo->times_eaten < philo->wisdom->num_to_eat)
	{	
		while(!philo->wisdom->death)
		{
			if (!philo->wisdom->forks[fork_right])
			{
				pthread_mutex_lock(philo->wisdom->mtx_forks + fork_right);
				philo->wisdom->forks[fork_right] = 1;
				ft_print_action(philo, "has taken a right fork", fork_right);//////////////////////////
				if (!philo->wisdom->forks[fork_left])
				{
					pthread_mutex_lock(philo->wisdom->mtx_forks + fork_left);
					philo->wisdom->forks[fork_left] = 1;
					
					ft_print_action(philo, "has taken a left  fork", fork_left);
					break ;
				}
				philo->wisdom->forks[fork_right] = 0;
				pthread_mutex_unlock(philo->wisdom->mtx_forks + fork_right);
			}
			else if(!philo->wisdom->forks[fork_left])
			{
				pthread_mutex_lock(philo->wisdom->mtx_forks + fork_left);
				philo->wisdom->forks[fork_left] = 1;
				ft_print_action(philo, "has taken a left  fork", fork_left); ////////////////////////////
				if (!philo->wisdom->forks[fork_right])
				{
					pthread_mutex_lock(philo->wisdom->mtx_forks + fork_right);
					philo->wisdom->forks[fork_right] = 1;
					
					ft_print_action(philo, "has taken a right fork", fork_right);
					break ;
				}
				philo->wisdom->forks[fork_left] = 0;
				pthread_mutex_unlock(philo->wisdom->mtx_forks + fork_left);
			}
			usleep(300);
		}
		
		ft_print_action(philo, "is eating", -1);
		usleep(us_to_eat);
		
		philo->wisdom->forks[fork_left] = 0;
		pthread_mutex_unlock(philo->wisdom->mtx_forks + fork_left);
		philo->wisdom->forks[fork_right] = 0;
		pthread_mutex_unlock(philo->wisdom->mtx_forks + fork_right);
		philo->times_eaten++; /////////////////////// or should thye break here???
		ft_print_action(philo, "is sleeping", -1);
		usleep(us_to_sleep);
		ft_print_action(philo, "is thinking", -1);
	}
}

void	ft_create_threads(t_wisdom *wisdom)
{
	int	i;

	wisdom->start = ft_usec_now();
	i = 0;
	while (i < wisdom->num_ph)
	{
		pthread_create(wisdom->threads + i, NULL, (void *)(&ft_philo_life), wisdom->philos[i]);
		wisdom->philos[i]->last_meal = ft_usec_now();
		i++;
	}
}

void	ft_join_threads(t_wisdom *wisdom)
{
	int	i;

	printf("Test\n");
	i = 0;
	while (i < wisdom->num_ph)
	// {
		pthread_join(wisdom->threads[i++], NULL);
		// i++;
	// }
	printf("Joined all\n");////////////////////////////////////////////
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

// usleep
// gettimeofday

// pthread_create
// pthread_detach
// pthread_join

// pthread_mutex_init
// pthread_mutex_destroy
// pthread_mutex_lock
// pthread_mutex_unlock


// timestamp_in_ms X has taken a fork
// timestamp_in_ms X is eating
// timestamp_in_ms X is sleeping
// timestamp_in_ms X is thinking
// timestamp_in_ms X died

// void	ft_philo_liffe(t_philo *philo)
// {
// 	int	fork_right;
// 	int	fork_left;
// 	long	us_to_eat;
// 	long	us_to_sleep;

// 	us_to_eat = philo->wisdom->us_to_eat;
// 	us_to_sleep = philo->wisdom->us_to_sleep;
// 	// if (philo->index == philo->wisdom->num_ph - 1)
// 	// {
// 		fork_left = (philo->index + 1) % philo->wisdom->num_ph;
// 		fork_right = philo->index;
// 	// }
// 	// else
// 	// {
// 	// 	fork_left = philo->index;
// 	// 	fork_right = (philo->index + 1) % philo->wisdom->num_ph;
// 	// }
// 	if (philo->index %2 == 0)
// 		usleep(1000);
// 	usleep(1000 * philo->index);
// 	while (!philo->wisdom->death)
// 	{	
// 		while(!philo->wisdom->death)
// 		{
// 			if (!philo->wisdom->forks[fork_right])
// 			{
// 				pthread_mutex_lock(philo->wisdom->mtx_forks + fork_right);
// 				// ft_print_action(philo, "has taken a right fork", fork_right);
// 				philo->wisdom->forks[fork_right] = 1;
// 				if (!philo->wisdom->forks[fork_left])
// 				{
// 					pthread_mutex_lock(philo->wisdom->mtx_forks + fork_left);
// 					gettimeofday(&philo->last_meal, NULL);
// 					ft_print_action(philo, "has taken a right fork", fork_right);//////////////////////////
// 					ft_print_action(philo, "has taken a left  fork", fork_left);
// 					philo->wisdom->forks[fork_left] = 1;
// 					break ;
// 				}
// 				philo->wisdom->forks[fork_right] = 0;
// 				pthread_mutex_unlock(philo->wisdom->mtx_forks + fork_right);
// 			}
// 			else if(!philo->wisdom->forks[fork_left])
// 			{
// 				pthread_mutex_lock(philo->wisdom->mtx_forks + fork_left);
// 				// ft_print_action(philo, "has taken a left  fork", fork_left);
// 				philo->wisdom->forks[fork_left] = 1;
// 				if (!philo->wisdom->forks[fork_right])
// 				{
// 					pthread_mutex_lock(philo->wisdom->mtx_forks + fork_right);
// 					gettimeofday(&philo->last_meal, NULL);
// 					ft_print_action(philo, "has taken a left  fork", fork_left); ////////////////////////////
// 					ft_print_action(philo, "has taken a right fork", fork_right);
// 					philo->wisdom->forks[fork_right] = 1;
// 					break ;
// 				}
// 				philo->wisdom->forks[fork_left] = 0;
// 				pthread_mutex_unlock(philo->wisdom->mtx_forks + fork_left);
// 			}
// 		}
		
// 		ft_print_action(philo, "is eating", -1);
// 		usleep(us_to_eat);
		
// 		philo->wisdom->forks[fork_left] = 0;
// 		pthread_mutex_unlock(philo->wisdom->mtx_forks + fork_left);
// 		philo->wisdom->forks[fork_right] = 0;
// 		pthread_mutex_unlock(philo->wisdom->mtx_forks + fork_right);
// 		ft_print_action(philo, "is sleeping", -1);
// 		usleep(us_to_sleep);
// 		ft_print_action(philo, "is thinking", -1);
// 	}
// }
