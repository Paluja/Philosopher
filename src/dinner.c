/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjimenez <pjimenez@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:34:11 by pjimenez          #+#    #+#             */
/*   Updated: 2024/05/30 19:01:45 by pjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void thinking(t_philo *philo, bool flag)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!flag)
		write_status(THINKING, philo, DEBUG);
	if (philo->table->philo_nbr % 2 == 0)
		return ;
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = (t_eat * 2) - t_sleep;
	if (t_think < 0)
		t_think = 0;
	p_usleep(t_think * 0.69, philo->table);
	write_status(THINKING, philo,DEBUG);
}

void* one_philo(void *data)
{
	t_philo	*philo;
	
	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex,&philo->last_meal_time,gettime(MILISECOND));
	increase_long(&philo->table->table_mutex,&philo->table->threads_running_nbr);
	write_status(TAKE_FIRST_FORK,philo,DEBUG);
	while (!simulation_finished(philo->table))
		p_usleep(200,philo->table);
	return (NULL);
	
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
	//set time de la last_meal
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILISECOND));
	//synchor with monitor
	//aumentar un contandor en table, con todo los hilos ejecutandose
	increase_long(&philo->table->table_mutex, 
			&philo->table->threads_running_nbr);

	//desincorniczar 
	
	while (!simulation_finished(philo->table))
	{
		// si esta full
		if (get_bool(&philo->philo_mutex, &philo->full)) //comprobar si el thread esta asegurado
			break ;
		eat(philo);

		write_status(SLEEPING,philo, DEBUG);
		p_usleep(philo->table->time_to_sleep,philo->table);

		thinking(philo, false);
		
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
	else if (table->philo_nbr == 1)
		safe_thread_handle(&table->philos[0].thread_id, 
				one_philo,&table->philos[0],CREATE);
    else if (table->limit_meals == 0)
        ; //caso especial
    else
    {
        while (table->philo_nbr > i)
		{
            safe_thread_handle(&table->philos[i].thread_id,dinner_simulation,
            	&table->philos[i],CREATE);
				i++;
		}
    }
	//monitor para si mueren  klk 
	safe_thread_handle(&table->monitor,monitor_dinner,table,CREATE);
	
	//start the dinner-> funcion para darnos el tiempo de cada accion
	table->start_cocking = gettime(MILISECOND);
	
	//despues de esto todos los threads estarian inicializados
	set_bool(&table->table_mutex, &table->all_threads_ok,true);

	// wait para todos
	i = 0;
	//comprueba que toodos los hilos hayan terminado antes de seguir la ejecucion
	while (table->philo_nbr > i)
	{
		safe_thread_handle(&table->philos[i].thread_id,NULL,NULL,JOIN); 
		i++;
	}
	set_bool(&table->table_mutex, &table->end_cocking, true);
	
	safe_thread_handle(&table->monitor,NULL,NULL,JOIN);
	

	
}