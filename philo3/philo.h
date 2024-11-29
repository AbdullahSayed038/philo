#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_philosopher
{
	int			id;
	int			meals_had;
	int			left_fork;
	int			right_fork;
	int			meals;
	ssize_t		time_of_last_meal;
	pthread_t	thread_id;
}	t_philosopher;

typedef struct s_input
{
	int				nb_of_philo;
	int				food_flag;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals;
	int				dead;
	ssize_t			program_start_time;
	pthread_mutex_t	check_death;
	pthread_mutex_t	*fork;
	pthread_mutex_t	printing;
	t_philosopher	*philosophers;
} t_input;

typedef struct s_life_args 
{
	int				index;
	t_input			*input;
	t_philosopher	*philosopher;
} t_life_args;

ssize_t time_taken(t_philosopher *philosopher, t_input *philo);
void 	set_death(t_input *philo, t_philosopher *philosopher, size_t index);

#endif