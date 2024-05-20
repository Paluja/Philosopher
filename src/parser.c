#include "philo.h"

static char *valid_input(const char *str)
{
    
}


static long ft_atol(const char **str)
{
    long    num;

    num = 0;
    str = valid_input(str);
}

void parser_input(t_table *table, char **av)
{
    table->philo_nbr = ft_atol(av[1]);
}