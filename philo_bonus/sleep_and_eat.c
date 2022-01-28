/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_and_eat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclassie <kclassie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:00:48 by kclassie          #+#    #+#             */
/*   Updated: 2022/01/26 20:01:28 by kclassie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	my_sleep(long time_to_wait)
{
	long	cur_time;
	long	period_of_time;

	cur_time = get_cur_time();
	period_of_time = get_cur_time() + time_to_wait;
	while (period_of_time > cur_time)
	{
		usleep(100);
		cur_time = get_cur_time();
	}
}


void	ft_output(t_phil_data *philo, char *str)
{
	sem_wait(philo->sems->output);
	if (philo->args->death_flag == 0)
		printf("%ld\tThe philo %d %s\n", get_cur_time() - philo->start_time, \
		philo->philo_id, str);
	sem_post(philo->sems->output);
}

int	eating(t_phil_data *philo)
{
	sem_wait(philo->sems->forks);
	ft_output(philo, "has taken the forks");
	ft_output(philo, "is eating");
	philo->last_meal = get_cur_time();
	my_sleep(philo->args->time_eat);
	sem_post(philo->sems->forks);
	return (0);
}
