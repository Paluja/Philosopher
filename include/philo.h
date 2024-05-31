/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjimenez <pjimenez@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:32:50 by pjimenez          #+#    #+#             */
/*   Updated: 2024/05/31 14:09:03 by pjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <errno.h>
# include <inttypes.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}						t_opcode;

typedef enum e_time_code
{
	SECOND,
	MILISECOND,
	MICROSECOND,
}						t_time_code;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}						t_philo_status;

typedef pthread_mutex_t	t_mutex;

typedef struct s_table	t_table;

typedef struct s_fork
{
	t_mutex				fork;
	int					fork_id;
}						t_fork;

typedef struct s_philo
{
	int					id;
	long				meals_counter;
	bool				full;
	long				last_meal_time;
	t_fork				*first_fork;
	t_fork				*second_fork;
	pthread_t			thread_id;
	t_mutex				philo_mutex;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	long				philo_nbr;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				limit_meals;
	long				start_cocking;
	long				threads_running_nbr;
	bool				end_cocking;
	bool				all_threads_ok;
	pthread_t			monitor;
	t_mutex				table_mutex;
	t_mutex				write_mutex;
	t_fork				*forks;
	t_philo				*philos;
}						t_table;

# define DEBUG 0

// Colorines
# define RST "\033[0m" /* Reset to default color */
# define RED "\033[1;31m" /* Bold Red */
# define G "\033[1;32m" /* Bold Green */
# define Y "\033[1;33m" /* Bold Yellow */
# define B "\033[1;34m" /* Bold Blue */
# define M "\033[1;35m" /* Bold Magenta */
# define C "\033[1;36m" /* Bold Cyan */
# define W "\033[1;37m" /* Bold White */

//UTILS
void					error_exit(const char *str);
long					gettime(t_time_code time_code);
void					p_usleep(long usec, t_table *table);
void					free_all(t_table *table);

//WIRTE
void					write_status(t_philo_status status, t_philo *philo);

//SYNCHRO UTILS
void					wait_all_threads(t_table *table);

//PARSER
void					parser_input(t_table *table, char **av);

//SAFE CONTROLS
void					*safe_malloc(size_t bytes);
void					safe_thread_handle(pthread_t *thread,
							void *(*foo)(void *),
							void *data,
							t_opcode opcode);
void					safe_mutex_handle(t_mutex *mutex, t_opcode opcode);

//DATA INIT
void					data_init(t_table *table);

//DINNER
void					start_coocking(t_table *table);
void					thinking(t_philo *philo, bool flag);

//syncro nosequie
void					wait_all_threads(t_table *table);
void					des_synchronize(t_philo *philo);

//MONITOR
bool					all_threads_running(t_mutex *mutex, long *threads,
							long philo_nbr);
void					increase_long(t_mutex *mutex, long *value);
void					*monitor_dinner(void *data);

//SETTERS AND GETTERS ---> codigo mas leible
void					set_bool(t_mutex *mutex, bool *dest, bool value);
bool					get_bool(t_mutex *mutex, bool *value);
void					set_long(t_mutex *mutex, long *dest, long value);
long					get_long(t_mutex *mutex, long *value);
bool					simulation_finished(t_table *table);
#endif