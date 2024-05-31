/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjimenez <pjimenez@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:50:35 by pjimenez          #+#    #+#             */
/*   Updated: 2024/05/31 14:07:31 by pjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	error_exit(const char *str)
{
	printf("%s\n", str);
	exit(EXIT_FAILURE);
}

long	gettime(t_time_code time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_exit("Error at gettimeofday");
	else if (time_code == SECOND)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (time_code == MILISECOND)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (time_code == MICROSECOND)
		return ((tv.tv_sec * 1e6) + (tv.tv_usec));
	else
		error_exit("Wrong time input");
	return (LONG_MAX);
}

void	p_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem;

	start = gettime(MICROSECOND);
	while (usec > gettime(MICROSECOND) - start)
	{
		if (simulation_finished(table))
			break ;
		elapsed = gettime(MICROSECOND) - start;
		rem = usec - elapsed;
		if (rem > 1e3)
			usleep(rem / 2);
		else
		{
			while (usec > gettime(MICROSECOND) - start)
				;
		}
	}
}

void	free_all(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (table->philo_nbr < i)
	{
		philo = table->philos + i;
		safe_mutex_handle(&philo->philo_mutex, DESTROY);
		i++;
	}
	safe_mutex_handle(&table->write_mutex, DESTROY);
	safe_mutex_handle(&table->table_mutex, DESTROY);
	free(table->forks);
	free(table->philos);
}
