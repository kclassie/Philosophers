/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_and_eat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclassie <kclassie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 19:59:18 by kclassie          #+#    #+#             */
/*   Updated: 2022/01/26 19:59:37 by kclassie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	my_sleep(long time_to_wait)
{
	long	cur_time;
	long	period_of_time;

	cur_time = get_time();
	period_of_time = get_time() + time_to_wait;
	while (period_of_time > cur_time)
	{
		usleep(100);
		cur_time = get_time();
	}
}

void	ft_output(t_phil_data *philo, char *str)
{
	pthread_mutex_lock(&philo->mutex->output);
	if (philo->args->flag == 1)
		return ;
	else if (philo->args->flag == 0)
	{
		printf("%ld\tThe philo %d %s\n", get_time()
			- philo->start_time, philo->philo_id, str);
		pthread_mutex_unlock(&philo->mutex->output);
	}
}

int	eating(t_phil_data *philo)
{
	pthread_mutex_lock(philo->r_fork);
	ft_output(philo, "has taken a right fork");
	pthread_mutex_lock(philo->l_fork);
	ft_output(philo, "has taken a left fork");
	ft_output(philo, "is eating");
	return (0);
}
