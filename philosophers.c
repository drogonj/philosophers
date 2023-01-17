/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:09:28 by ngalzand          #+#    #+#             */
/*   Updated: 2023/01/16 11:09:33 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*check_death(void *arg)
{
	long long	i;
	t_struct	*main_struct;

	main_struct = (t_struct *)arg;
	while (!main_struct->death)
	{
		i = -1;
		while (!main_struct->death && ++i < main_struct->number_of_philosophers)
		{
			if (get_time() - main_struct->time_start - main_struct
				->philosophers[i].last_dinner >= main_struct->time_to_die)
			{
				main_struct->death = 1;
				pthread_mutex_lock(&main_struct->printf_mutex);
				printf(BLACK "%lld %lld died\n" RESET, get_time()
					- main_struct->time_start, i + 1);
				ft_exit(free_struct(main_struct), 0);
			}
		}
	}
	pthread_exit(arg);
}

static void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_l);
	pthread_mutex_lock(&philo->main_struct->printf_mutex);
	printf(BLUE "%lld %ld has taken a fork\n" RESET, get_time()
		- philo->main_struct->time_start, philo->who);
	pthread_mutex_unlock(&philo->main_struct->printf_mutex);
	pthread_mutex_lock(philo->fork_r);
	pthread_mutex_lock(&philo->main_struct->printf_mutex);
	printf(BLUE "%lld %ld has taken a fork\n" RESET, get_time()
		- philo->main_struct->time_start, philo->who);
	pthread_mutex_unlock(&philo->main_struct->printf_mutex);
}

static void	eat(t_philo *philo)
{
	philo->last_dinner = get_time() - philo->main_struct->time_start;
	philo->main_struct->meal_counter++;
	pthread_mutex_lock(&philo->main_struct->printf_mutex);
	printf(MAGENTA "%lld %ld is eating\n" RESET, get_time()
		- philo->main_struct->time_start, philo->who);
	pthread_mutex_unlock(&philo->main_struct->printf_mutex);
	usleep_remake(philo->main_struct->time_to_eat);
	pthread_mutex_unlock(&philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
}

static void	sleep_and_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->main_struct->printf_mutex);
	printf(GREEN "%lld %ld is sleeping\n" RESET, get_time()
		- philo->main_struct->time_start, philo->who);
	pthread_mutex_unlock(&philo->main_struct->printf_mutex);
	usleep_remake(philo->main_struct->time_to_sleep);
	pthread_mutex_lock(&philo->main_struct->printf_mutex);
	printf(YELLOW "%lld %ld is thinking\n" RESET, get_time()
		- philo->main_struct->time_start, philo->who);
	pthread_mutex_unlock(&philo->main_struct->printf_mutex);
}

void	*philosophers_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->who % 2 != 0)
		usleep_remake(philo->main_struct->time_to_eat / 2);
	while (!philo->main_struct->death)
	{
		take_forks(philo);
		eat(philo);
		if (philo->main_struct->duration_each_must_eat != -1
			&& philo->main_struct->meal_counter
			>= philo->main_struct->duration_each_must_eat
			* philo->main_struct->number_of_philosophers)
		{
			pthread_mutex_lock(&philo->main_struct->printf_mutex);
			printf(CYAN "All philosophers have eaten %lld times\n" RESET,
				philo->main_struct->duration_each_must_eat);
			ft_exit(free_struct(philo->main_struct), 0);
		}
		sleep_and_think(philo);
	}
	pthread_exit(arg);
}
