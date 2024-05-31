/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjimenez <pjimenez@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:50:41 by pjimenez          #+#    #+#             */
/*   Updated: 2024/05/31 13:42:44 by pjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_philos(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < table->philo_nbr)
	{
		philo = table->philos + i;
		printf("Philo %d\n", philo->id);
		printf("Meals %ld\n", philo->meals_counter);
		printf("First fork %d\n", philo->first_fork->fork_id);
		printf("Second fork %d\n", philo->second_fork->fork_id);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_table	*table;

	table = safe_malloc(sizeof(t_table));
	if (ac == 5 || ac == 6)
	{
		parser_input(table, av);
		data_init(table);
		start_coocking(table);
		free_all(table);
	}
	else
	{
		error_exit("Bad arguments");
		free(table);
	}
	return (0);
}
