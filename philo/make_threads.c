/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclassie <kclassie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:00:22 by kclassie          #+#    #+#             */
/*   Updated: 2022/01/26 20:00:25 by kclassie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_and_free(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->args->philo_num)
	{
		pthread_mutex_destroy(all->philos[i].l_fork);
		pthread_mutex_destroy(all->philos[i].r_fork);
		free(all->philos[i].mutex);
		i++;
	}
	pthread_mutex_destroy(&all->mutexes->output);
	free(all->mutexes->forks);
	free(all->mutexes);
	free(all->philos);
}

void	*start_act(void *ph_struct)
{
	t_phil_data	*philo;

	philo = (t_phil_data *)ph_struct;
	philo->last_meal = get_time();
	pthread_detach(philo->thread);
	while (1)
	{
		if (philo->eat_count != 0)
		{
			eating(philo);
			philo->last_meal = get_time();
			philo->eat_count--;
			my_sleep(philo->args->time_to_eat);
			pthread_mutex_unlock(philo->r_fork);
			pthread_mutex_unlock(philo->l_fork);
			ft_output(philo, "is sleeping");
			my_sleep(philo->args->time_to_sleep);
			ft_output(philo, "is thinking");
		}
		else
			break ;
	}
	return (NULL);
}

int	make_thread(t_all *all_info, int flag, int i)
{
	if (all_info->philos[i].philo_id % 2 == flag)
	{
		all_info->philos[i].start_time = all_info->args->time;
		all_info->philos[i].mutex = malloc(sizeof(t_mutexes));
		if (!all_info->philos[i].mutex)
		{
			destroy_mutexes(all_info);
			free(all_info->mutexes);
			free(all_info->mutexes->forks);
			return (put_error("Memory's not allocated", 0));
		}
		if (pthread_create(&all_info->philos[i].thread, NULL, &start_act,
				&all_info->philos[i]) != 0)
		{
			destroy_mutexes(all_info);
			free(all_info->mutexes);
			free(all_info->mutexes->forks);
			return (put_error("Thread can't be created", 0));
		}
	}
	usleep(30);
	return (0);
}

int	philo_thread(t_all *all_info)
{
	int	i;

	i = -1;
	all_info->args->time = get_time();
	while (++i < all_info->args->philo_num)
		make_thread(all_info, 0, i);
	i = -1;
	usleep(10);
	while (++i < all_info->args->philo_num)
		make_thread(all_info, 1, i);
	if (pthread_create(&all_info->dead, NULL, &check_dead, all_info) != 0)
		return (put_error("Thread can't be created", 0));
	if (pthread_join(all_info->dead, NULL) != 0)
		return (put_error("Thread can't be joined", 0));
	destroy_and_free(all_info);
	return (0);
}
