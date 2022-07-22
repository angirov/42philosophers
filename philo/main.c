/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 19:19:29 by vangirov          #+#    #+#             */
/*   Updated: 2022/07/21 20:04:22 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_philo
{
	/* data */
}	t_philo;

typedef struct s_table
{
	char	*plate;
	char	**forks;
}	t_table;

typedef struct s_wisdom
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
	t_philo	philos;
	t_table	table;
}	t_wisdom;

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

void	ft_init(int argc, char **argv, t_wisdom *wisdom)
{
	if (!ft_is_format(argc, argv))
		exit(0); /////////////////////////////////////////////////////////////////////////////////////////////////////
	wisdom->number_of_philosophers = argv[1];
	wisdom->time_to_die = argv[2];
	wisdom->time_to_eat = argv[3];
	wisdom->time_to_sleep = argv[4];
	if (argc == 6)
		wisdom->number_of_times_each_philosopher_must_eat = argv[5];
	else
		wisdom->number_of_times_each_philosopher_must_eat = 0;
	ft_init_philos();
	ft_init_table();
}

int	main(int argc, char **argv)
{
	t_wisdom	wisdom;

	ft_init(argc, argv, &wisdom);
	
}