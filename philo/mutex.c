/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 20:43:21 by vangirov          #+#    #+#             */
/*   Updated: 2022/09/11 20:44:01 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_death(t_wisdom *wisdom)
{
	int	death;

	pthread_mutex_lock(&wisdom->mtx_death);
	death = wisdom->death;
	pthread_mutex_unlock(&wisdom->mtx_death);
	return (death);
}

void	set_death(t_wisdom *wisdom, int value)
{
	pthread_mutex_lock(&wisdom->mtx_death);
	wisdom->death = value;
	pthread_mutex_unlock(&wisdom->mtx_death);
}

int	get_done(t_wisdom *wisdom)
{
	int	done;

	pthread_mutex_lock(&wisdom->mtx_done);
	done = wisdom->done;
	pthread_mutex_unlock(&wisdom->mtx_done);
	return (done);
}

void	set_done(t_wisdom *wisdom, int value)
{
	pthread_mutex_lock(&wisdom->mtx_done);
	wisdom->done = value;
	pthread_mutex_unlock(&wisdom->mtx_done);
}
