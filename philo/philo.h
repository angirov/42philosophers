/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 10:29:10 by vangirov          #+#    #+#             */
/*   Updated: 2022/09/05 20:57:16 by vangirov         ###   ########.fr       */
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
# include <stdint.h>

typedef struct s_wisdom	t_wisdom;
typedef struct s_philo	t_philo;
typedef struct timeval	t_tv;

struct s_philo
{
	t_wisdom		*wisdom;
	int				index;
	int				number;
	int64_t			last_meal;
	int64_t			death_time;
	pthread_mutex_t	mtx_last;
	int				times_eaten;
};

struct s_wisdom
{
	int				death;
	int				done;
	int				num_ph;
	int64_t			us_to_die;
	int64_t			us_to_eat;
	int64_t			us_to_sleep;
	int				num_to_eat;
	t_philo			**philos;
	int				*forks;
	int64_t			start;
	pthread_t		*threads;
	pthread_mutex_t	mtx_print;
	pthread_mutex_t	*mtx_forks;
};

int			ft_isdigit(int c);
int			ft_atoi(const char *nptr);
long		ft_atol(const char *nptr);
int			ft_is_format(int argc, char **argv);
int			ft_init(int argc, char **argv, t_wisdom *wisdom);
int			ft_free(t_wisdom *wisdom);

int64_t		ft_usec_now(void);
void		ft_wait(int64_t usec_wait);

void		ft_print_time(t_wisdom *wisdom);
void		ft_print_action(t_philo *philo, const char *action, int fork);
void		ft_print(t_philo *philo, const char *action, int fork);
void		ft_philo_life(t_philo *philo);
void		ft_god(t_wisdom *wisdom);

#endif