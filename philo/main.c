/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 19:19:29 by vangirov          #+#    #+#             */
/*   Updated: 2022/07/26 23:48:08 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_philo_life(t_philo *philo)
{
	int	fork_right;
	int	fork_left;
	long	us_to_eat;
	long	us_to_sleep;

	us_to_eat = philo->wisdom->us_to_eat;
	us_to_sleep = philo->wisdom->us_to_sleep;
	fork_left = (philo->index + 1) % philo->wisdom->num_ph;
	fork_right = philo->index;
	if (philo->index %2 == 0) //philo->index == philo->wisdom->num_ph - 1)
	{
		usleep(1000);
	}
	// else
	// {
	// 	fork_left = philo->index;
	// 	fork_right = (philo->index + 1) % philo->wisdom->num_ph;
	// }
	while (1)
	{	
		// while(philo->wisdom->forks[fork_right] || philo->wisdom->forks[fork_left])
		// {
		// 	// usleep(20*1000);
		// 	// printf("Ph %2d checks: R [%d] = %d,check: L [%d] = %d\n", 
		// 	// 	philo->index,
		// 	// 	fork_right, philo->wisdom->forks[fork_right], 
		// 	// 	fork_left, philo->wisdom->forks[fork_left]);
		// 	continue ;
		// }
		pthread_mutex_lock(philo->wisdom->mtx_forks + fork_right);
		// philo->wisdom->forks[fork_right] = 1;
		ft_print_action(philo, "has taken a right fork", fork_right);

		pthread_mutex_lock(philo->wisdom->mtx_forks + fork_left);
		// philo->wisdom->forks[fork_left] = 1;
		ft_print_action(philo, "has taken a left  fork", fork_left);
		
		gettimeofday(&philo->last_meal, NULL);
		ft_print_action(philo, "is eating", -1);
		usleep(us_to_eat);
		
		// philo->wisdom->forks[fork_left] = 0;
		pthread_mutex_unlock(philo->wisdom->mtx_forks + fork_left);
		// philo->wisdom->forks[fork_right] = 0;
		pthread_mutex_unlock(philo->wisdom->mtx_forks + fork_right);
		ft_print_action(philo, "is sleeping", -1);
		usleep(us_to_sleep);
		ft_print_action(philo, "is thinking", -1);
	}
}

void	ft_create_threads(t_wisdom *wisdom)
{
	int	i;

	i = 0;
	while (i < wisdom->num_ph)
	{
		pthread_create(wisdom->threads + i, NULL, (void *)(&ft_philo_life), wisdom->philos[i]);
		i++;
	}
}

void	ft_join_threads(t_wisdom *wisdom)
{
	int	i;

	i = 0;
	while (i < wisdom->num_ph)
	// {
		pthread_join(wisdom->threads[i++], NULL);
		// i++;
	// }
	// printf("Joined all\n");
}

void	ft_god(t_wisdom *wisdom)
{
	int	i;
	long	us_to_die;

	us_to_die = wisdom->us_to_die;
	i = 0;
	while (1)
	{
		if (ft_usec_diff(wisdom->philos[i]->last_meal) > us_to_die)
		{
			wisdom->death = 1;
			break ;
		}
		i = (i + 1) % wisdom->num_ph;
		// printf("Check philo %2d\n", i);
	}
	ft_print(wisdom->philos[i], "died", ft_usec_diff(wisdom->philos[i]->last_meal) / 1000);
	// free...
}

int	main(int argc, char **argv)
{
	t_wisdom	wisdom;
	int			i;

	ft_init(argc, argv, &wisdom);
	ft_create_threads(&wisdom);
	ft_god(&wisdom);
	ft_join_threads(&wisdom);

	pthread_mutex_destroy(&wisdom.mtx_print);
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
