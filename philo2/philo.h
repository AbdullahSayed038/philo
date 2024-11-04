#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>

struct s_philo;

typedef struct	s_philosopher
{
	int				id;
	int				meals;
	int				left_fork;
	int				right_fork;
	ssize_t			last_meal;
	struct s_philo 	philo;
	pthread_t		thread_id;
}	t_philosopher;


typedef struct	s_philo
{
	int					nb_of_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					meals;
	int					dead;
	int					satisfaction;
	ssize_t				start_time;
	pthread_mutext_t	meal_counter;
	pthread_mutext_t	fork[250];
	pthread_mutext_t	printing;
	t_philosopher		philosopher[250];
}	t_philo;

#endif