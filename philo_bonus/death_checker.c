/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclassie <kclassie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:00:53 by kclassie          #+#    #+#             */
/*   Updated: 2022/01/26 20:01:31 by kclassie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	death_checker(t_phil_data *philos)
{
	long	hunger_time;

	hunger_time = get_cur_time() - philos->last_meal;
	if (philos->args->time_to_die < hunger_time)
	{
		ft_output(philos, "is dead");
		return (0);
	}
	return (1);
}

void	*check_dead(void *philos)
{
	t_phil_data	*phil;
	int			meals_count;
	long		hunger_time;

	phil = (t_phil_data *)philos;
	while (1)
	{
		meals_count = 0;
		hunger_time = get_cur_time() - phil->last_meal;
		if (phil->args->time_to_die < hunger_time)
		{
			sem_wait(phil->sems->output);
			printf("%ld\tThe philo %d is dead\n", get_cur_time() - \
			phil->start_time, phil->philo_id);
			exit (0);
		}
		meals_count += phil->eat_count;
		if (meals_count == 0)
		{
			sem_wait(phil->sems->output);
			exit (0);
		}
	}
}
