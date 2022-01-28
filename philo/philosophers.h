/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclassie <kclassie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:00:16 by kclassie          #+#    #+#             */
/*   Updated: 2022/01/26 20:00:17 by kclassie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_mutexes
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	output;
}			t_mutexes;

typedef struct s_data
{
	int		philo_num;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		num_of_meals;
	int		flag;
	long	time;
}				t_data;

typedef struct s_phil_data
{
	int				philo_id;
	int				eat_count;
	long			start_time;
	long			last_meal;
	t_data			*args;
	t_mutexes		*mutex;
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}				t_phil_data;

typedef struct s_all
{
	pthread_t	dead;
	t_data		*args;
	t_mutexes	*mutexes;
	t_phil_data	*philos;
}				t_all;

long	get_time(void);
int		eating(t_phil_data *philo);
void	my_sleep(long time_to_wait);
int		philo_thread(t_all *all_info);
void	destroy_mutexes(t_all *all);
void	ft_output(t_phil_data *philo, char *str);
void	*check_dead(void *all_data);

int		ft_isdigit(int c);
int		ft_atoi(char *str);
int		put_error(char *error_message, int error_id);
int		argc_parsing(char **argv);

#endif