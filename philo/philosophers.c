/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclassie <kclassie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:00:06 by kclassie          #+#    #+#             */
/*   Updated: 2022/01/26 20:00:11 by kclassie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_phil(t_all *all_info)
{
	int	i;

	i = 0;
	all_info->philos = malloc(sizeof(t_phil_data) * \
	all_info->args->philo_num);
	if (!all_info->philos)
		return (1);
	while (i < all_info->args->philo_num)
	{
		all_info->philos[i].philo_id = i + 1;
		all_info->philos[i].last_meal = 0;
		all_info->philos[i].eat_count = all_info->args->num_of_meals;
		all_info->philos[i].args = all_info->args;
		all_info->philos[i].mutex = all_info->mutexes;
		all_info->philos[i].r_fork = &all_info->mutexes->forks[i];
		if ((i + 1) == all_info->args->philo_num)
			all_info->philos[i].l_fork = &all_info->mutexes->forks[0];
		else
			all_info->philos[i].l_fork = &all_info->mutexes->forks[i + 1];
		i++;
	}
	return (0);
}

int	init_mutex(t_all *all_info)
{
	int	i;

	i = 0;
	all_info->mutexes = malloc(sizeof(t_mutexes));
	if (!all_info->mutexes)
		return (put_error("Memory's not been allocated", 0));
	all_info->mutexes->forks = malloc(sizeof(pthread_mutex_t)
			* all_info->args->philo_num);
	if (!all_info->mutexes->forks)
		return (put_error("Memory's not allocated", 0));
	if (pthread_mutex_init(&all_info->mutexes->output, NULL))
		return (put_error("Mutex's not been inited", 0));
	while (i < all_info->args->philo_num)
	{
		if (pthread_mutex_init(&all_info->mutexes->forks[i], NULL))
			return (put_error("Mutex's not been inited", 0));
		i++;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_all	all_info;
	t_data	data;

	all_info.args = &data;
	if ((argc < 5 || argc > 6))
		return (put_error("Arguments error\n", 1));
	if (!argc_parsing(argv))
		return (put_error("Arguments error\n", 1));
	all_info.args->philo_num = ft_atoi(argv[1]);
	all_info.args->time_to_die = ft_atoi(argv[2]);
	all_info.args->time_to_eat = ft_atoi(argv[3]);
	all_info.args->time_to_sleep = ft_atoi(argv[4]);
	all_info.args->num_of_meals = -1;
	all_info.args->flag = 0;
	if (argc > 5)
		all_info.args->num_of_meals = ft_atoi(argv[5]);
	if (init_mutex(&all_info))
		return (0);
	if (init_phil(&all_info))
		return (0);
	if (philo_thread(&all_info))
		return (0);
}
