/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 20:41:01 by vangirov          #+#    #+#             */
/*   Updated: 2022/09/05 20:42:48 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
