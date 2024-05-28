/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjimenez <pjimenez@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:40:08 by pjimenez          #+#    #+#             */
/*   Updated: 2024/05/28 19:22:52 by pjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"



static void	write_status_debug(t_philo_status status, t_philo *philo,
		long elapsed)
{
	if (TAKE_FIRST_FORK == status && !simulation_finished(philo->table))
		printf(W"%6ld"RST" %d has taken the 1° fork 🍽"
			"\t\t\tn°"B"[🍴 %d 🍴]\n"RST, elapsed, philo->id,
			philo->first_fork->fork_id);
	else if (TAKE_SECOND_FORK == status && !simulation_finished(philo->table))
		printf(W"%6ld"RST" %d has taken the 2° fork 🍽"
			"\t\t\tn°"B"[🍴 %d 🍴]\n"RST, elapsed, philo->id,
			philo->second_fork->fork_id);
	else if (EATING == status && !simulation_finished(philo->table))
		printf(W"%6ld"C" %d is eating 🍝"
			"\t\t\t"Y"[🍝 %ld 🍝]\n"RST, elapsed, philo->id, philo->meals_counter);
	else if (SLEEPING == status && !simulation_finished(philo->table))
		printf(W"%6ld"RST" %d is sleeping 😴\n", elapsed, philo->id);
	else if (THINKING == status && !simulation_finished(philo->table))
		printf(W"%6ld"RST" %d is thinking 🤔\n", elapsed, philo->id);
	else if (DIED == status)
		printf(RED"\t\t💀💀💀 %6ld %d died   💀💀💀\n"RST, elapsed, philo->id);
}



void write_status(t_philo_status status, t_philo *philo, bool debug)
{
	long	elapsed;
	
	elapsed = gettime(MILISECOND) - philo->table->start_cocking;
	if (philo->full)
		return ;
	safe_mutex_handle(&philo->table->write_mutex,LOCK);
	
	if (debug)
		write_status_debug(status,philo,elapsed);
	else
	{
		if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK )
				&& !simulation_finished(philo->table))
				printf(W"%-6ld"RST" %d has taken a fork\n", elapsed, philo->id);
		else if (status == EATING && !simulation_finished(philo->table))
			printf(W"%-6ld"C" %d is eating\n"RST, elapsed, philo->id);
		else if (status==SLEEPING && !simulation_finished(philo->table))
			printf(W"%-6ld"RST" %d is sleeping\n", elapsed, philo->id);
		else if (status==THINKING && !simulation_finished(philo->table))
			printf(W"%-6ld"RST" %d is thinking\n", elapsed, philo->id);
		else if (status == DIED)
			printf(RED"%-6ld %d died\n"RST, elapsed, philo->id);
	}
	safe_mutex_handle(&philo->table->write_mutex,UNLOCK);
}