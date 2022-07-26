/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 19:19:29 by vangirov          #+#    #+#             */
/*   Updated: 2022/07/26 20:18:21 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
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

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s)
	{
		len++;
		s++;
	}
	return (len);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

int	ft_digittonum(char c)
{
	int	num;

	num = c - '0';
	return (num);
}


int	ft_atoi(const char *nptr)
{
	int	num;
	int	minus;

	num = 0;
	minus = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '+')
		nptr++;
	else if (*nptr == '-')
	{
		minus = 1;
		nptr++;
	}
	while (ft_isdigit(*nptr))
		num = num * 10 + ft_digittonum(*nptr++);
	if (minus)
		num *= -1;
	return (num);
}

long	ft_atol(const char *nptr)
{
	long	num;
	int		minus;

	num = 0;
	minus = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '+')
		nptr++;
	else if (*nptr == '-')
	{
		minus = 1;
		nptr++;
	}
	while (ft_isdigit(*nptr))
		num = num * 10 + (*nptr++ - '0');
	if (minus)
		num *= -1;
	return (num);
}

int	ft_is_good_num(char *str)
{
	long	n;

	n = 0;
	while (str[n])
	{
		if (ft_strlen(str) > 1 && n == 0 && str[0] == '-')
			n++;
		else if (!ft_isdigit(str[n++]))
			return (0);
	}
	n = ft_atol(str);
	if (n > INT_MAX || n < INT_MIN)
		return (0);
	if (n < 0)
		return (0);
	return (1);
}

int	ft_is_format(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (0);
	i = 1;
	while (argv[i])
	{
		if (!ft_is_good_num(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_set_params(int argc, char **argv, t_wisdom *wisdom)
{
	wisdom->num_ph = ft_atoi(argv[1]);
	wisdom->us_to_die = ft_atoi(argv[2]) * 1000;
	wisdom->us_to_eat = ft_atoi(argv[3])* 1000;
	wisdom->us_to_sleep = ft_atoi(argv[4])* 1000;
	if (argc == 6)
		wisdom->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		wisdom->number_of_times_each_philosopher_must_eat = 0;
}

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

long	ft_print_time(void)
{
	t_tv	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

void	ft_init(int argc, char **argv, t_wisdom *wisdom)
{
	int	i;
	
	gettimeofday(&wisdom->start, NULL);
	printf("Start: %ld:%ld\n", wisdom->start.tv_sec, wisdom->start.tv_usec);
	
	if (!ft_is_format(argc, argv))
	{
		printf("Bad imput: usage: philo number_of_philosophers ");
		printf("ms_to_die ms_to_eat ms_to_sleep ");
		printf("[number_of_times_each_philosopher_must_eat]\n");
		exit(0); /////////////////////////////////////////////////
	}
	ft_set_params(argc, argv, wisdom);
	wisdom->forks = malloc(sizeof(int) * wisdom->num_ph);
	wisdom->philos = malloc(sizeof(t_philo *) * wisdom->num_ph);
	wisdom->threads = malloc(sizeof(pthread_t) * wisdom->num_ph);
	pthread_mutex_init(&wisdom->mtx_print, NULL);
	wisdom->mtx_forks = malloc(sizeof(pthread_mutex_t) * wisdom->num_ph);
	i = 0;
	while (i < wisdom->num_ph)
	{
		wisdom->philos[i] = malloc(sizeof(t_philo));
		wisdom->philos[i]->wisdom = wisdom;
		wisdom->philos[i]->index = i;
		wisdom->philos[i]->last_meal = wisdom->start;
		wisdom->forks[i] = 0;
		pthread_mutex_init(&wisdom->mtx_forks[i], NULL);
		i++;
	}
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

// void	ft_msleep(int	msec)
// {
// 	usleep(msec * 1000);
// }

void	ft_grab_fork(t_wisdom *wisdom, int fork_i)
{
	pthread_mutex_lock(wisdom->mtx_forks + fork_i);
	
	pthread_mutex_unlock(wisdom->mtx_forks + fork_i);
}

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
	{
		pthread_join(wisdom->threads[i], NULL);
		i++;
	}
	printf("Joined all\n");
}

long	ft_usec_diff(t_tv last_meal)
{
	long	diff_sec;
	long	diff_usec;
	t_tv	now;

	gettimeofday(&now, NULL);
	diff_sec = now.tv_sec - last_meal.tv_sec;
	diff_usec = (now.tv_usec - last_meal.tv_usec);
	if (diff_usec < 0)
	{
		diff_sec--;
		diff_usec = 1000000 + diff_usec;
	}
	return(diff_sec * 1000000 + diff_usec);
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
			break ;
		}
		i = (i + 1) % wisdom->num_ph;
		// printf("Check philo %2d\n", i);
	}
	ft_print_action(wisdom->philos[i], "died", ft_usec_diff(wisdom->philos[i]->last_meal) / 1000);
	// free...
	exit(42);
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