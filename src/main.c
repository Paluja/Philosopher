/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjimenez <pjimenez@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:50:41 by pjimenez          #+#    #+#             */
/*   Updated: 2024/05/20 19:00:34 by pjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int main(int ac, char **av)
{
    t_table *table;
    table = safe_malloc(sizeof(t_table));
    if (ac == 5 || ac == 6)
    {
        parser_input(table,av);

        //data_init

        //start_coocking

        //clean
    }
    else{
        error_exit("Bad arguments");
    }
    return (0);
}