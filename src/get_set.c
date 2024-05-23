/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjimenez <pjimenez@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:28:40 by pjimenez          #+#    #+#             */
/*   Updated: 2024/05/23 18:46:15 by pjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

//para evitar estar todo el rato escribiendo lock y unlock

void    set_bool(t_mutex *mutex, bool *dest, bool value)
{
    safe_mutex_handle(mutex,LOCK);
    *dest = value;
    safe_mutex_handle(mutex,UNLOCK);
}

bool	get_bool(t_mutex *mutex, bool value)
{
	bool	res;
    safe_mutex_handle(mutex,LOCK);
    res = value;
    safe_mutex_handle(mutex,UNLOCK);
	return(res);
}

void    set_long(t_mutex *mutex, long *dest, long value)
{
    safe_mutex_handle(mutex,LOCK);
    *dest = value;
    safe_mutex_handle(mutex,UNLOCK);
}

bool	get_long(t_mutex *mutex, long value)
{
	long	res;
    safe_mutex_handle(mutex,LOCK);
    res = value;
    safe_mutex_handle(mutex,UNLOCK);
	return(res);
}

bool simulation_finished(t_table *table)
{
	return (get_bool(&table->table_mutex, table->end_cocking));
}