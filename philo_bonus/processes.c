/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclassie <kclassie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:01:09 by kclassie          #+#    #+#             */
/*   Updated: 2022/01/26 20:01:40 by kclassie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_all(t_all *all)
{
	sem_unlink("output");
	sem_unlink("forks");
	sem_close(all->sems->output);
	sem_close(all->sems->forks);
	free(all->sems);
	free(all->philos->pid);
	free(all->philos);
}

void	start_act(t_phil_data *phil)
{
	pthread_t	dead_flag;

	phil->start_time = get_cur_time();
	phil->last_meal = get_cur_time();
	pthread_create(&dead_flag, NULL, check_dead, (void *)phil);
	pthread_detach(dead_flag);
	while (1)
	{
		if (phil->eat_count != 0)
		{
			eating(phil);
			phil->eat_count--;
			ft_output(phil, "is sleeping");
			my_sleep(phil->args->time_sleep);
			ft_output(phil, "is thinking");
		}
		else
			exit (0);
	}
}

void	wait_loop(t_all *all)
{
	int	i;
	int	j;
	int	status;

	i = 0;
	while (i < all->args->phil_num)
	{
		waitpid(-1, &status, 0);
		if (status == 0)
		{
			j = 0;
			while (j < all->args->phil_num)
			{
				kill(all->philos->pid[j], SIGTERM);
				j++;
			}
		}
		i++;
	}
}

int	init_process(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->args->phil_num)
	{
		all->philos->pid[i] = fork();
		if (all->philos->pid[i] == 0)
		{
			all->philos->philo_id = i + 1;
			start_act(all->philos);
		}
		else if (all->philos->pid[i] == -1)
			return (put_error("Can't create a process\n", 0));
		i++;
	}
	wait_loop(all);
	return (0);
}
