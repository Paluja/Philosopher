/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjimenez <pjimenez@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:50:30 by pjimenez          #+#    #+#             */
/*   Updated: 2024/05/20 18:52:41 by pjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	is_space(char c)
{
	if (c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v'
	        || c == ' ')
	        return (true);
	return (false);
}

static bool     is_digit(int c)
{
        return ((c >= 48 && c <= 57) || (c == 43 || c == 45));
}

static char *valid_input(char *str)
{
    int len;
    char *nbr;

    len = 0;
    while (is_space(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		error_exit("Negative number are not allowed >:|");
	if (!is_digit(*str))
		error_exit("The input have to be a number");
	nbr = str;
	while (is_digit(*str++))
		len++;
	if (len > 10)
		error_exit("The value pass the INT_MAX");
	return(nbr);
}


static long ft_atol(char *str)
{
    long    num;

    num = 0;
    str = valid_input(str);
	while (is_digit(*str))
		num = (num * 10) + (*str++ - 48);
	if (num > INT_MAX)
		error_exit("The value pass the INT_MAX");
	return (num);
	
}

void parser_input(t_table *table, char **av)
{
    table->philo_nbr = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * 1e3;
	table->time_to_eat = ft_atol(av[3]) * 1e3;
	table->time_to_sleep = ft_atol(av[4]) * 1e3;
	if (table->time_to_die < 6e4
		|| table->time_to_eat < 6e4
		|| table->time_to_sleep < 6e4)
		error_exit("Timestamps have to be major tha 60ms");
	if (av[5])
		table->limit_meals = ft_atol(av[5]);
	else
		table->limit_meals = -1;
}