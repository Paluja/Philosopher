/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjimenez <pjimenez@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:32:50 by pjimenez          #+#    #+#             */
/*   Updated: 2024/05/23 19:11:51 by pjimenez         ###   ########.fr       */
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
#include	<limits.h>
#include	<errno.h>

//options codes para mutex y threads
typedef enum	e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}		t_opcode;

//coder para el tiempo
typedef enum	e_time_code
{
	SECOND,
	MILISECOND,
	MICROSECOND,
}		t_time_code;




typedef	pthread_mutex_t t_mutex;
typedef struct s_table t_table;
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
	t_fork	*first_fork;
	t_fork	*second_fork;
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
	bool	all_threads_ok; //para sincronizar los philos
	t_mutex	table_mutex; //evista los races mientras se esta leyendo la mesa
	t_fork	*forks;
	t_philo	*philos;
}				t_table;

//UTILS
void    error_exit(const char *str);
long	gettime(t_time_code time_code);

//SYNCHRO UTILS
void wait_all_threads(t_table *table);

//PARSER
void parser_input(t_table *table, char **av);

//SAFE CONTROLS
void* safe_malloc(size_t bytes);
void safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data,
     t_opcode opcode);
void    safe_mutex_handle(t_mutex *mutex, t_opcode opcode);

//DATA INIT
void data_init(t_table *table);

//SETTERS AND GETTERS ---> codigo mas leible
void    set_bool(t_mutex *mutex, bool *dest, bool value);
bool	get_bool(t_mutex *mutex, bool value);
void    set_long(t_mutex *mutex, long *dest, long value);
bool	get_long(t_mutex *mutex, long value);
bool simulation_finished(t_table *table);
#endif