/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 20:41:10 by vangirov          #+#    #+#             */
/*   Updated: 2022/07/26 20:41:14 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_print_time(void)
{
	t_tv	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

void	ft_print_action(t_philo *philo, const char *action, int fork)
{
	pthread_mutex_lock(&philo->wisdom->mtx_print);
	printf("[%ld] ", ft_print_time());
	if (fork >=0)
		printf("Philo %2d %s [%d]\n", philo->index, action, fork);
	else
		printf("Philo %2d %s\n", philo->index, action);
	pthread_mutex_unlock(&philo->wisdom->mtx_print);
}
