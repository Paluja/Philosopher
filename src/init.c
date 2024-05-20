/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjimenez <pjimenez@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:47:07 by pjimenez          #+#    #+#             */
/*   Updated: 2024/05/20 19:11:15 by pjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void assign_forks(t_philo *philo, t_fork forks, int position)



static void philo_init(t_table *table)
{
    int		i;
    t_philo	*philo;
	
	i = 0;
	
	while (i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->meals_counter = 0;
		philo->table = table;
		//assign_fork
		i++;
	}
	
    
}



void data_init(t_table *table)
{
    int i;

    i = 0;
    table->end_cocking = false;
    table->philos = safe_malloc(sizeof(table->philo_nbr));
    table->forks = safe_malloc(sizeof(table->forks));
    while (i < table->philo_nbr)
    {
        safe_mutex_handle(&table->forks[i].fork,INIT);
        table->forks[i].fork_id = i;
        i++;
    }
    philo_init(table);
    
}