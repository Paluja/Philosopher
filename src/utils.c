/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjimenez <pjimenez@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:50:35 by pjimenez          #+#    #+#             */
/*   Updated: 2024/05/20 18:50:51 by pjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void    error_exit(const char *str)
{
    printf("%s\n",str);
    exit(EXIT_FAILURE);
}