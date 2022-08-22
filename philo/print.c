/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 20:41:10 by vangirov          #+#    #+#             */
/*   Updated: 2022/07/27 17:26:08 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_time(t_wisdom *wisdom)
{
	int64_t	now;

	now = ft_usec_now() - wisdom->start;
	printf("[%03ld:%06ld]", now / 1000000, now % 1000000);
}

// void	ft_print_action(t_philo *philo, const char *action, int fork)
// {
// 	pthread_mutex_lock(&philo->wisdom->mtx_print);
// 	printf("[%ld] ", ft_print_time(philo->wisdom));
// 	if (fork >=0)
// 		printf("%2d %s [%d]\n", philo->index, action, fork);
// 	else
// 		printf("%2d %s\n", philo->index, action);
// 	pthread_mutex_unlock(&philo->wisdom->mtx_print);
// }

typedef	struct s_print
{
	t_philo		*philo;
	const char	*action;
	int			num;
} t_print;

void	ft_print_action_thread(t_print *task)
{
	t_philo		*philo;
	const char	*action;
	int			num;
	
	philo = task->philo;
	action = task->action;
	num = task->num;
	ft_print(philo, action, num);
	pthread_exit(NULL);
}

void	ft_print_action(t_philo *philo, const char *action, int num)
{
	pthread_t	thread;
	t_print		*task;

	task = malloc(sizeof(t_print));
	task->philo = philo;
	task->action = action;
	task->num = num;
	pthread_create(&thread, NULL, (void *)(&ft_print_action_thread), task);
	pthread_detach(thread);
}

void	ft_print(t_philo *philo, const char *action, int fork)
{
	pthread_mutex_lock(&philo->wisdom->mtx_print);
	ft_print_time(philo->wisdom);
	if (fork >=0)
		printf(" %2d %s [%d]\n", philo->index, action, fork);
	else
		printf(" %2d %s\n", philo->index, action);
	pthread_mutex_unlock(&philo->wisdom->mtx_print);
}
