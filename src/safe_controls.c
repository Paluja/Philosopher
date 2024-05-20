/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_controls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjimenez <pjimenez@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:02:19 by pjimenez          #+#    #+#             */
/*   Updated: 2024/05/20 18:55:19 by pjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void* safe_malloc(size_t bytes)
{
    void    *result;
    
    result = malloc(bytes);
    if (result == NULL)
        error_exit("Malloc error");
    return(result);
}

static void handle_mutex_error(int status,t_opcode opcode)
{
    if (status == 0)
        return ;
    if(status == EINVAL && (opcode == LOCK || opcode == UNLOCK || opcode == DESTROY))
        error_exit("The value specified by mutex is invalid");
    else if (status == EINVAL && opcode == INIT)
        error_exit("The value specified by attr is invalid");
    else if (status == EDEADLK)
        error_exit("A deadlock would occur if the thread blocked waiting for mutex");
    else if (status == EPERM)
        error_exit("The current thread does not hold a lock on mutex");
    else if (status == ENOMEM)
        error_exit("The process cannot allocate enough memory to create another mutex");
    else if (status == EBUSY)
        error_exit("Mutex is locked");
}


void    safe_mutex_handle(t_mutex *mutex, t_opcode opcode)
{
    if (opcode == LOCK)
        handle_mutex_error(pthread_mutex_lock(mutex), opcode);
    else if (opcode == UNLOCK)
        handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
    else if (opcode == INIT)
        handle_mutex_error(pthread_mutex_init(mutex,NULL), opcode);
    else if (opcode == DESTROY)
        handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
    else
        error_exit("Wrong opcode for mutex");
}


static void handle_thread_error(int status, t_opcode opcode)
{
    if (status == 0)
        return ;
    if (opcode == EAGAIN)
        error_exit("No resources to create anotrher thread\n");
    else if(opcode == EPERM)
        error_exit("The caller does not hace appropriate permisiion\n");
    else if(opcode == EINVAL)
        error_exit("The value specified by attr is invalid\n");
    else if(opcode == EINVAL)
        error_exit("The value specified by thread is no joinable\n");
    else if(opcode == ESRCH)
        error_exit("No thread could be found corresponding to that"
            	"specified by the given thread ID, thread");
    else if(opcode == EDEADLK)
        error_exit("A deadlock was detected or the value of"
        "thread specifies the calling thread");
}

void safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data,
     t_opcode opcode)
{
    if (opcode == CREATE)
        handle_thread_error(pthread_create(thread,NULL,foo,data),opcode);
    else if (opcode == JOIN)
        handle_thread_error(pthread_join(*thread,NULL),opcode);
    else if (opcode == DETACH)
        handle_thread_error(pthread_detach(*thread),opcode);
    else
        error_exit("Wrong opcode for thread_handle");
}