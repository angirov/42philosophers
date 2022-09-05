/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 20:41:10 by vangirov          #+#    #+#             */
/*   Updated: 2022/09/05 20:42:26 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_time(t_wisdom *wisdom)
{
	int64_t	now;

	now = ft_usec_now() - wisdom->start;
	printf("[%03lld:%03lld]", now / 1000000, (now % 1000000) / 1000);
}

void	ft_print_action(t_philo *philo, const char *action, int fork)
{
	pthread_mutex_lock(&philo->wisdom->mtx_print);
	ft_print_time(philo->wisdom);
	if (fork >= 0)
		printf("%2d %s [%d]\n", philo->number, action, fork);
	else
		printf("%2d %s\n", philo->number, action);
	pthread_mutex_unlock(&philo->wisdom->mtx_print);
}
