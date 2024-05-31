/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjimenez <pjimenez@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:28:40 by pjimenez          #+#    #+#             */
/*   Updated: 2024/05/31 13:52:49 by pjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	set_bool(t_mutex *mutex, bool *dest, bool value)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK);
}

bool	get_bool(t_mutex *mutex, bool *value)
{
	bool	ret;

	safe_mutex_handle(mutex, LOCK);
	ret = *value;
	safe_mutex_handle(mutex, UNLOCK);
	return (ret);
}

long	get_long(t_mutex *mutex, long *value)
{
	long	ret;

	safe_mutex_handle(mutex, LOCK);
	ret = *value;
	safe_mutex_handle(mutex, UNLOCK);
	return (ret);
}

void	set_long(t_mutex *mutex, long *dest, long value)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK);
}

bool	simulation_finished(t_table *table)
{
	return (get_bool(&table->table_mutex, &table->end_cocking));
}
