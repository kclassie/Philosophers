/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclassie <kclassie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 19:59:47 by kclassie          #+#    #+#             */
/*   Updated: 2022/01/26 19:59:50 by kclassie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_mutexes(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->args->philo_num)
		pthread_mutex_destroy(&all->mutexes->forks[i++]);
	pthread_mutex_destroy(&all->mutexes->output);
}

int	death_checker(t_phil_data *philos)
{
	long	hunger_time;

	hunger_time = get_time() - philos->last_meal;
	if (philos->args->time_to_die < hunger_time)
	{
		pthread_mutex_lock(&philos->mutex->output);
		printf("%ld\tThe philo %d is dead\n", get_time()
			- philos->start_time, philos->philo_id);
		philos->args->flag = 1;
		return (0);
	}
	return (1);
}

void	*check_dead(void *all_data)
{
	t_all	*all;
	int		i;
	int		meals_count;

	all = (t_all *)all_data;
	while (1)
	{
		i = 0;
		meals_count = 0;
		while (i < all->args->philo_num)
		{
			if (!death_checker(&all->philos[i]))
				return (NULL);
			meals_count += all->philos[i].eat_count;
			i++;
		}
		if (meals_count == 0)
		{
			pthread_mutex_lock(&all->mutexes->output);
			return (NULL);
		}
	}
}
