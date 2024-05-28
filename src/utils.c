/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjimenez <pjimenez@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:50:35 by pjimenez          #+#    #+#             */
/*   Updated: 2024/05/28 19:20:23 by pjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void    error_exit(const char *str)
{
    printf("%s\n",str);
    exit(EXIT_FAILURE);
}

long	gettime(t_time_code time_code)
{
	struct	timeval	tv;
	
	if (gettimeofday(&tv,NULL))
		error_exit("Error at gettimeofday");
	else if(time_code == SECOND)
		return (tv.tv_sec + (tv.tv_usec/1e6));
	else if(time_code == MILISECOND)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec/1e3));
	else if(time_code == MICROSECOND)
		return ((tv.tv_sec * 1e6) + (tv.tv_usec));
	else
		error_exit("Wrong time input");
	return(LONG_MAX);
}

void p_usleep(long usec,t_table *table)//  usec/2 =====> rem/2
{
	long	start;
	long	elapsed;
	long	rem;
	
	start = gettime(MICROSECOND);
	while (usec > gettime(MICROSECOND) - start)
	{
		if (simulation_finished(table))
			break ;
		elapsed = gettime(MICROSECOND) - start; //el tiempo transcurrido desde que empezo
		rem = usec - elapsed;
		if (rem > 1e3)
			usleep(rem/2);
		else
		{
			while (usec > gettime(MICROSECOND) - start)
				;
		}
	}
}