/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 20:54:57 by vangirov          #+#    #+#             */
/*   Updated: 2022/09/05 20:55:35 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
