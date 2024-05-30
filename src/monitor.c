/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjimenez <pjimenez@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:39:43 by pjimenez          #+#    #+#             */
/*   Updated: 2024/05/29 20:17:27 by pjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool philo_died(t_philo *philo)
{
	long	elapsed;
	
	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed = gettime(MILISECOND) - get_long(&philo->philo_mutex, 
				&philo->last_meal_time);
	if (elapsed > (philo->table->time_to_die / 1e3))
		return(true);
	return (false);
			
}



void*   monitor_dinner(void *data)
{
	t_table	*table;
    int		i;

	table = (t_table *)data;
	while (!all_threads_running(&table->table_mutex,&table->threads_running_nbr,
				table->philo_nbr))
		;
	while (!simulation_finished(table))
	{
		i = 0;
		while (i< table->philo_nbr && !simulation_finished(table))
		{
			if (philo_died(table->philos + i))
			{
				set_bool(&table->table_mutex, &table->end_cocking, true);
				write_status(DIED, table->philos + i, DEBUG);
			}
			i++;
		}
				
	}
	return(NULL);
}

bool	all_threads_running(t_mutex *mutex, long *threads, long philo_nbr)
{
	bool ret;
	
	ret = false;
	safe_mutex_handle(mutex,LOCK);
	if (*threads == philo_nbr)
		ret = true;
	safe_mutex_handle(mutex,UNLOCK);
	return (ret);

}



//para sincronizarse con el monitor
void increase_long(t_mutex *mutex, long *value)
{
	safe_mutex_handle(mutex,LOCK);
	(*value)++;
	safe_mutex_handle(mutex,UNLOCK);
}