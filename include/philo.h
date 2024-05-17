/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjimenez <pjimenez@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:32:50 by pjimenez          #+#    #+#             */
/*   Updated: 2024/05/17 18:22:04 by pjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <stdint.h>
# include <stdbool.h>
# include <inttypes.h>
# include <stdint.h>

typedef	pthread_mutex_t t_mutex;

//METETLE COLORES AL PRINTF QUE QUEDA WAPO





typedef struct s_fork
{
	t_mutex	fork;
	int	fork_id;
}		t_fork;


typedef struct s_philo
{
    int	id;
	long	meals_counter;
	bool	full; //para ver si ha comido todas las veces que tenia que comer
	long	last_meal_time; //tiempo desde la ultima comida
	t_fork	*left_fork;
	t_fork	*right_fork;
	pthread_t	thread_id;
	t_table		*table;
}				t_philo;


typedef	struct	s_table
{
	long 	philo_nbr;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	limit_meals;
	long	start_cocking;
	bool	end_cocking;
	t_fork	*forks;
	t_philo	*philos;
}				t_table;


void    error_exit(const char *str);



#endif