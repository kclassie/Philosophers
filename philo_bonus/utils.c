/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclassie <kclassie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:01:16 by kclassie          #+#    #+#             */
/*   Updated: 2022/01/26 20:01:43 by kclassie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	put_error(char *error_message, int error_id)
{
	printf("\nError: ");
	printf("%s\n", error_message);
	if (error_id == 1)
	{
		printf("Taken arguments:\n");
		printf("1. number_of_philosophers\n");
		printf("2. time_to_die (in milliseconds)\n");
		printf("3. time_to_eat (in milliseconds)\n");
		printf("4. time_to_sleep (in milliseconds)\n");
		printf("5. number_of_times_each_philosopher_must_eat (optional)\n\n");
	}
	return (1);
}

int	ft_isdigit(int c)
{
	if (('9' >= c) && (c >= '0'))
		return (1);
	else
		return (0);
}

int	ft_atoi(char *str)
{
	int				neg;
	unsigned long	nb;

	neg = 1;
	nb = 0;
	while (*str == ' ' || (*str > 8 && *str < 14))
		str++;
	if (*str == '-')
		neg = neg * -1;
	if (*str == '+' || *str == '-')
		str++;
	while ('0' <= *str && *str <= '9')
	{
		nb = (nb * 10) + (*str - 48);
		str++;
		if (nb > __INT_MAX__)
			return (-1);
	}
	return (nb * neg);
}

long	get_cur_time(void)
{
	struct timeval	time;
	long			res;

	gettimeofday(&time, NULL);
	res = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (res);
}

