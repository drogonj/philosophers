/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:09:17 by ngalzand          #+#    #+#             */
/*   Updated: 2023/01/16 11:09:20 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	init_philosophers(t_struct *philo)
{
	long long	i;

	i = -1;
	philo->time_start = get_time();
	pthread_create(&philo->death_thread, NULL, &check_death, philo);
	while (++i < philo->number_of_philosophers)
	{
		philo->philosophers[i].who = i + 1;
		philo->philosophers[i].last_dinner = 0;
		philo->philosophers[i].main_struct = philo;
		pthread_mutex_init(&(philo->philosophers[i].fork_l), NULL);
		philo->philosophers[i].fork_r = &(philo->philosophers[(i + 1)
				% philo->number_of_philosophers].fork_l);
		pthread_create(&philo->philosophers[i].thread, NULL,
			&philosophers_routine, &(philo->philosophers[i]));
	}
	i = -1;
	while (++i < philo->number_of_philosophers)
		pthread_join(philo->philosophers[i].thread, NULL);
	pthread_join(philo->death_thread, NULL);
}

static t_struct	*init_struct(int argc, char **argv)
{
	t_struct	*philo;

	philo = (t_struct *)malloc(sizeof(t_struct));
	if (!philo)
		ft_exit(NULL, printf(RED "Error\n" RESET));
	philo->meal_counter = 0;
	philo->number_of_philosophers = ft_atoi(argv[1], philo);
	philo->time_to_die = ft_atoi(argv[2], philo);
	philo->time_to_eat = ft_atoi(argv[3], philo);
	philo->time_to_sleep = ft_atoi(argv[4], philo);
	pthread_mutex_init(&(philo->printf_mutex), NULL);
	philo->death = 0;
	if (philo->number_of_philosophers == 0)
		ft_exit(free_struct(philo), printf(RED "Error\n" RESET));
	if (argc == 6)
		philo->duration_each_must_eat = ft_atoi(argv[5], philo);
	else
		philo->duration_each_must_eat = -1;
	philo->philosophers = (t_philo *)malloc
		(sizeof(t_philo) * philo->number_of_philosophers);
	if (!philo->philosophers)
		ft_exit(free_struct(philo), printf(RED "Error\n" RESET));
	return (philo);
}

static int	check_args(int argc, char **argv)
{
	int	n;
	int	i;

	n = 0;
	if (argc != 5 && argc != 6)
		return (1);
	while (++n < argc)
	{
		i = -1;
		while (argv[n][++i])
			if (argv[n][i] < '0' || argv[n][i] > '9')
				return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_struct	*philo;

	if (check_args(argc, argv) == 1)
		ft_exit(NULL, printf(RED "Error\n" RESET));
	philo = init_struct(argc, argv);
	init_philosophers(philo);
	free_struct(philo);
	return (0);
}
