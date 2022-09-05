/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 20:41:21 by vangirov          #+#    #+#             */
/*   Updated: 2022/09/05 20:43:06 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int64_t	ft_usec_now(void)
{
	t_tv		now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000000 + now.tv_usec);
}

void	ft_wait(int64_t usec_wait)
{
	int64_t	usec_end;

	usec_end = ft_usec_now() + usec_wait;
	while (ft_usec_now() < usec_end)
	{
		usleep(50);
	}
	return ;
}

// long	ft_usec_diff(t_tv last_meal)
// {
// 	long	diff_sec;
// 	long	diff_usec;
// 	t_tv	now;

// 	gettimeofday(&now, NULL);
// 	diff_sec = now.tv_sec - last_meal.tv_sec;
// 	diff_usec = (now.tv_usec - last_meal.tv_usec);
// 	if (diff_usec < 0)
// 	{
// 		diff_sec--;
// 		diff_usec = 1000000 + diff_usec;
// 	}
// 	return(diff_sec * 1000000 + diff_usec);
// }

// void	ft_msleep(int	msec)
// {
// 	usleep(msec * 1000);
// }

// long	ft_msec_diff(t_tv before, t_tv after)
// {
// 	long	diff_sec;
// 	long	diff_msec;

// 	diff_sec = after.tv_sec - before.tv_sec;
// 	diff_msec = (after.tv_usec - before.tv_usec) / 1000;
// 	if (diff_msec < 0)
// 	{
// 		diff_sec--;
// 		diff_msec = 1000 + diff_msec;
// 	}
// 	return(diff_sec * 1000 + diff_msec);
// }

// void	ft_now_usec(t_wisdom *wisdom)
// {
// 	t_tv	now;
// 	long	diff_sec;
// 	long	diff_usec;

// 	gettimeofday(&now, NULL);
// 	diff_sec = now.tv_sec - wisdom->start.tv_sec;
// 	diff_usec = now.tv_usec - wisdom->start.tv_usec;
// 	if (diff_usec < 0)
// 	{
// 		diff_sec--;
// 		diff_usec = 1000000 + diff_usec;
// 	}
// 	printf("[%02ld:%06ld] ", diff_sec, diff_usec);
// }

// void	ft_now_msec(t_wisdom *wisdom)
// {
// 	t_tv	now;
// 	long	diff_sec;
// 	long	diff_msec;

// 	gettimeofday(&now, NULL);
// 	diff_sec = now.tv_sec - wisdom->start.tv_sec;
// 	diff_msec = (now.tv_usec - wisdom->start.tv_usec) / 1000;
// 	if (diff_msec < 0)
// 	{
// 		diff_sec--;
// 		diff_msec = 1000 + diff_msec;
// 	}
// 	printf("[%02ld:%03ld] ", diff_sec, diff_msec);
// }
