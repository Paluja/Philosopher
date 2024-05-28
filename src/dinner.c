/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjimenez <pjimenez@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:34:11 by pjimenez          #+#    #+#             */
/*   Updated: 2024/05/28 19:40:49 by pjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void thinking(t_philo *philo)
{
	write_status(THINKING, philo,DEBUG);
}

static void eat(t_philo *philo)
{
//--------------LOCK los tenedores
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo, DEBUG);
	safe_mutex_handle(&philo->second_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo, DEBUG);
//----------- UPDATE MEALS AND WRITE STATUS
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILISECOND));
	philo->meals_counter++;
	write_status(EATING, philo, DEBUG);
	p_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->limit_meals > 0
		&& philo->meals_counter == philo->table->limit_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
//-----------------UNLOCK
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}


void* dinner_simulation(void *data)
{
	t_philo *philo;
	
	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	while (!simulation_finished(philo->table))
	{
		// si esta full
		if (philo->full) //comprobar si el thread esta asegurado
			break ;
		eat(philo);

		write_status(SLEEPING,philo, DEBUG);
		p_usleep(philo->table->time_to_sleep,philo->table);

		thinking(philo);
		
	}
	

	return(NULL);
}


//1 crear todoso threads
//2 crear un monitor para cada thread
//3 Sincronizar el comienzo de la comida de todos los threads
    //--> pthread_create : philo se inicializa
    // todos los philos se tienen que inicializar simultaneamente
//4 JOIN de todo


void start_coocking(t_table *table)
{
    int i;

    i = 0;
    if (table->limit_meals == 0)
        return ;
    else if (table->limit_meals == 0)
        ; //caso especial
    else
    {
        while (table->philo_nbr > i)
            safe_thread_handle(&table->philos[i].thread_id,dinner_simulation,
            	&table->philos[i],CREATE);
    }
	//start the dinner-> funcion para darnos el tiempo de cada accion
	table->start_cocking = gettime(MILISECOND);
	
	//despues de esto todos los threads estarian inicializados
	set_bool(&table->table_mutex, &table->all_threads_ok,true);

	// wait para todos
	i = 0;
	//comprueba que toodos los hilos hayan terminado antes de seguir la ejecucion
	while (table->philo_nbr > i++)
		safe_thread_handle(&table->philos[i].thread_id,NULL,NULL,JOIN); 
	set_bool(&table->table_mutex, &table->end_cocking, true);
	

	
}