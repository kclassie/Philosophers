/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclassie <kclassie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:01:04 by kclassie          #+#    #+#             */
/*   Updated: 2022/01/26 20:01:37 by kclassie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/time.h>

typedef struct s_sema
{
	sem_t	*forks;
	sem_t	*output;
}				t_sema;

typedef struct s_data
{
	int	phil_num;
	int	time_sleep;
	int	time_eat;
	int	time_to_die;
	int	num_of_meals;
	int	death_flag;
}				t_data;

typedef struct s_phil_data
{
	int				philo_id;
	pid_t			*pid;
	int				eat_count;
	long			start_time;
	long			last_meal;
	t_data			*args;
	t_sema			*sems;
}				t_phil_data;

typedef struct s_all
{
	t_data		*args;
	t_sema		*sems;
	t_phil_data	*philos;
}				t_all;

void	ft_output(t_phil_data *philo, char *str);
int		eating(t_phil_data *philo);
void	my_sleep(long time_to_wait);
void	*check_dead(void *all_data);
void	start_act(t_phil_data *phil);
long	get_cur_time(void);
void	free_all(t_all *all);
int		init_process(t_all *all);
void	wait_loop(t_all *all);
int		ft_isdigit(int c);
int		ft_atoi(char *str);
int		put_error(char *err, int error_id);

#endif