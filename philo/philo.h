/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 10:29:10 by vangirov          #+#    #+#             */
/*   Updated: 2022/07/26 20:48:05 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <time.h>

typedef struct s_wisdom t_wisdom;
typedef struct s_philo t_philo;
typedef struct timeval t_tv;

struct s_philo
{
	t_wisdom	*wisdom;
	int			index;
	t_tv		last_meal;
};

struct s_wisdom
{
	int				death;
	int				num_ph;
	long			us_to_die;
	long			us_to_eat;
	long			us_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	t_philo			**philos;
	int				*forks;
	t_tv			start;
	pthread_t		*threads;
	pthread_mutex_t	mtx_print;
	pthread_mutex_t	*mtx_forks;
};

int		ft_isdigit(int c);
int		ft_atoi(const char *nptr);
long	ft_atol(const char *nptr);
void	ft_init(int argc, char **argv, t_wisdom *wisdom);
long	ft_usec_diff(t_tv last_meal);
long	ft_print_time(void);
void	ft_print_action(t_philo *philo, const char *action, int fork);


#endif