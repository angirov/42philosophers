/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 20:41:10 by vangirov          #+#    #+#             */
/*   Updated: 2022/10/05 12:34:48 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#if defined(__linux__)

void	ft_print_time(t_wisdom *wisdom)
{
	int64_t	now;

	now = ft_usec_now() - wisdom->start;
	printf("[%03ld:%03ld]", now / 1000000, (now % 1000000) / 1000);
}

#elif defined(__APPLE__)

void	ft_print_time(t_wisdom *wisdom)
{
	int64_t	now;

	now = ft_usec_now() - wisdom->start;
	printf("[%03lld:%03lld]", now / 1000000, (now % 1000000) / 1000);
}

#endif

void	ft_print_action(t_philo *philo, const char *action, int fork)
{
	if (get_death(philo->wisdom))
		return ;
	pthread_mutex_lock(&philo->wisdom->mtx_print);
	ft_print_time(philo->wisdom);
	if (fork >= 0)
		printf("%2d %s [%d]\n", philo->number, action, fork);
	else
		printf("%2d %s\n", philo->number, action);
	pthread_mutex_unlock(&philo->wisdom->mtx_print);
}
