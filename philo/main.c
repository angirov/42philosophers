/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 19:19:29 by vangirov          #+#    #+#             */
/*   Updated: 2022/07/22 21:36:38 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

typedef struct s_philo
{
	int	last_meal;
}	t_philo;

typedef struct s_wisdom
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
	t_philo	**philos;
	int	*forks;
}	t_wisdom;

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
	wisdom->number_of_philosophers = ft_atoi(argv[1]);
	wisdom->time_to_die = ft_atoi(argv[2]);
	wisdom->time_to_eat = ft_atoi(argv[3]);
	wisdom->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		wisdom->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		wisdom->number_of_times_each_philosopher_must_eat = 0;
}

void	ft_init(int argc, char **argv, t_wisdom *wisdom)
{
	int	i;

	if (!ft_is_format(argc, argv))
		exit(0); /////////////////////////////////////////////////////////////////////////////////////////////////////
	ft_set_params(argc, argv, wisdom);
	wisdom->forks = malloc(sizeof(int) * wisdom->number_of_philosophers);
	wisdom->philos = malloc(sizeof(t_philo *) * \
						(wisdom->number_of_philosophers + 1));
	i = 0;
	while (i < wisdom->number_of_philosophers)
	{
		wisdom->philos[i] = malloc(sizeof(t_philo));
		wisdom->philos[i]->last_meal = wisdom->time_to_eat;
		wisdom->forks[i] = 42;
		i++;
	}
	wisdom->philos[i] = NULL;
}

int	main(int argc, char **argv)
{
	t_wisdom	wisdom;

	ft_init(argc, argv, &wisdom);
	return (0);
}