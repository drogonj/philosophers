/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:09:46 by ngalzand          #+#    #+#             */
/*   Updated: 2023/01/16 11:09:49 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*free_struct(t_struct *philo)
{
	long long	i;

	if (!philo)
		return (0);
	i = -1;
	if (philo->philosophers)
	{
		while (++i < philo->number_of_philosophers)
			pthread_detach(philo->philosophers[i].thread);
		i = -1;
		while (++i < philo->number_of_philosophers)
			pthread_mutex_destroy(&philo->philosophers[i].fork_l);
		free(philo->philosophers);
	}
	pthread_mutex_destroy(&philo->printf_mutex);
	free(philo);
	return (0);
}

void	ft_exit(void *null, int null_bis)
{
	(void)null;
	(void)null_bis;
	exit(EXIT_FAILURE);
}

void	usleep_remake(long long waiting_time)
{
	long long	start_time;
	long long	actual_time;

	start_time = get_time();
	actual_time = 0;
	while (actual_time - start_time < waiting_time)
	{
		usleep(250);
		actual_time = get_time();
	}
}

long long	get_time(void)
{
	struct timeval		time_info;
	long long			result;

	gettimeofday(&time_info, NULL);
	result = (time_info.tv_sec * 1000) + (time_info.tv_usec / 1000);
	return (result);
}

int	ft_atoi(const char *str, t_struct *philo)
{
	size_t			i;
	int				sign;
	long long int	res;

	i = 0;
	sign = 1;
	res = 0;
	while ((str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || str[i] == '\f'
			|| str[i] == '\r' || str[i] == ' '))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = ((res * 10) + str[i] - '0');
		i++;
	}
	if (res < -2147483648 || res > 2147483647)
		ft_exit(free_struct(philo), printf(RED "Error\n" RESET));
	return (res * sign);
}
