#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>

typedef struct	s_philo
{
	int		nb_of_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		meals;
	int		dead;
	int		satisfaction;
	ssize_t	start_time;
}

#endif