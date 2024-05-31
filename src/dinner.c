/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjimenez <pjimenez@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:34:11 by pjimenez          #+#    #+#             */
/*   Updated: 2024/05/31 14:04:26 by pjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	thinking(t_philo *philo, bool flag)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!flag)
		write_status(THINKING, philo);
	if (philo->table->philo_nbr % 2 == 0)
		return ;
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = (t_eat * 2) - t_sleep;
	if (t_think < 0)
		t_think = 0;
	p_usleep(t_think * 0.69, philo->table);
	write_status(THINKING, philo);
}

void	*one_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILISECOND));
	increase_long(&philo->table->table_mutex,
		&philo->table->threads_running_nbr);
	write_status(TAKE_FIRST_FORK, philo);
	while (!simulation_finished(philo->table))
		p_usleep(200, philo->table);
	return (NULL);
}

static void	eat(t_philo *philo)
{
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo);
	safe_mutex_handle(&philo->second_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILISECOND));
	philo->meals_counter++;
	write_status(EATING, philo);
	p_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->limit_meals > 0
		&& philo->meals_counter == philo->table->limit_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILISECOND));
	increase_long(&philo->table->table_mutex,
		&philo->table->threads_running_nbr);
	des_synchronize(philo);
	while (!simulation_finished(philo->table))
	{
		if (get_bool(&philo->philo_mutex, &philo->full))
			break ;
		eat(philo);
		write_status(SLEEPING, philo);
		p_usleep(philo->table->time_to_sleep, philo->table);
		thinking(philo, false);
	}
	return (NULL);
}

void	start_coocking(t_table *table)
{
	int	i;

	i = -1;
	if (table->limit_meals == 0)
		return ;
	else if (table->philo_nbr == 1)
		safe_thread_handle(&table->philos[0].thread_id, one_philo,
			&table->philos[0],
			CREATE);
	else if (table->limit_meals == 0)
		;
	else
	{
		while (table->philo_nbr > ++i)
			safe_thread_handle(&table->philos[i].thread_id, dinner_simulation,
				&table->philos[i], CREATE);
	}
	safe_thread_handle(&table->monitor, monitor_dinner, table, CREATE);
	table->start_cocking = gettime(MILISECOND);
	set_bool(&table->table_mutex, &table->all_threads_ok, true);
	i = -1;
	while (table->philo_nbr > ++i)
		safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
	set_bool(&table->table_mutex, &table->end_cocking, true);
	safe_thread_handle(&table->monitor, NULL, NULL, JOIN);
}
