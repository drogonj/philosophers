/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:09:36 by ngalzand          #+#    #+#             */
/*   Updated: 2023/01/16 11:10:32 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define RESET	"\033[0m"
# define RED 	"\033[31m"
# define GREEN   "\033[32m"
# define BLUE    "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN    "\033[36m"
# define BLACK	"\033[30m"
# define YELLOW	"\033[33m"

typedef struct s_philo
{
	long				who;
	pthread_t			thread;
	pthread_mutex_t		fork_l;
	pthread_mutex_t		*fork_r;
	long long			last_dinner;
	struct s_struct		*main_struct;
}						t_philo;

typedef struct s_struct
{
	t_philo			*philosophers;
	long long		time_start;
	long long		number_of_philosophers;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		duration_each_must_eat;
	long long		meal_counter;
	pthread_mutex_t	printf_mutex;
	pthread_t		death_thread;
	long long		death;
}					t_struct;

void		*main_thread(void *arg);
void		*philosophers_routine(void *arg);
void		*check_death(void *arg);

void		ft_exit(void *null, int null_bis);
int			ft_isdigit(int c);
void		usleep_remake(long long waiting_time);
int			ft_atoi(const char *str, t_struct *philo);
long long	get_time(void);
void		*free_struct(t_struct *philo);

#endif
