/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclassie <kclassie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:00:58 by kclassie          #+#    #+#             */
/*   Updated: 2022/01/26 20:01:34 by kclassie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_phil(t_all *all)
{
	all->philos = malloc(sizeof(t_phil_data) * all->args->phil_num);
	if (all->philos == NULL)
		return (1);
	all->philos->pid = malloc(sizeof(pid_t) * all->args->phil_num);
	if (all->philos->pid == NULL)
		return (1);
	all->args->death_flag = 0;
	all->philos->eat_count = all->args->num_of_meals;
	all->philos->args = all->args;
	all->philos->sems = all->sems;
	return (0);
}

int	init_sems(t_all *all)
{
	all->sems = malloc(sizeof(t_sema));
	if (all->sems == NULL)
		return (put_error("Memory's not been allocated", 0));
	sem_unlink("output");
	all->sems->output = sem_open("output", O_CREAT, 0644, 1);
	if (all->sems->output == SEM_FAILED)
		return (put_error("Semaphore failed to open", 0));
	sem_unlink("forks");
	all->sems->forks = sem_open("forks", O_CREAT, 0644, \
	all->args->phil_num / 2);
	if (all->sems->forks == SEM_FAILED)
		return (put_error("Semaphore failed to open", 0));
	return (0);
}

int	argc_parsing(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
			if (!ft_isdigit(argv[i][j++]) || ft_atoi(argv[i]) == -1)
				return (0);
		i++;
	}
	return (1);
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
	all_info.args->phil_num = ft_atoi(argv[1]);
	all_info.args->time_to_die = ft_atoi(argv[2]);
	all_info.args->time_eat = ft_atoi(argv[3]);
	all_info.args->time_sleep = ft_atoi(argv[4]);
	all_info.args->num_of_meals = -1;
	if (argc > 5)
		all_info.args->num_of_meals = ft_atoi(argv[5]);
	if (init_sems(&all_info))
		return (0);
	if (init_phil(&all_info))
		return (0);
	if (init_process(&all_info))
		return (0);
	free_all(&all_info);
}
