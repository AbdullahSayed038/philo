#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <limits.h>

struct s_philo;


typedef struct	s_philosopher
{
	int				id;
	int				meals;
	int				left_fork;
	int				right_fork;
	ssize_t			last_meal;
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
	pthread_mutex_t		meal_counter;
	pthread_mutex_t		death_checker;
	pthread_mutex_t		fork[250];
	pthread_mutex_t		printing;
	t_philosopher		philosopher[250];
}	t_philo;

typedef struct s_life_args {
	t_philosopher *philosopher;
	t_philo *philo;
	int index;
} t_life_args;

ssize_t	ft_strlen(char *str);
void	exitfree(t_philo *philo, char *msg, int fd, int exit_code);
int	ft_atoi_philo(char *str);
void	initialize_philosophers(t_philo *philo);
ssize_t	initialize_mutex_locks(t_philo *philo);
void	initialize_philo(t_philo *philo, char **av);
void	set_death(t_philo *philo, t_philosopher *philosopher, size_t index);
void	sleep_the_action(int time);
ssize_t get_current_time(void);
ssize_t	get_current_program_time(t_philo *philo);
ssize_t check_all_satisfaction(t_philo *philo);
ssize_t	time_taken(t_philosopher *philosopher, t_philo *philo);
void	eating(t_philosopher	*philosopher, t_philo *philo, int index);
void	sleeping(t_philosopher	*philosopher, t_philo *philo, int index);
void	thinking(t_philosopher	*philosopher, t_philo *philo, int index);
void	action(t_philo *philo, t_philosopher *philosopher, int nb, const char *str);
ssize_t	death_alarm(t_philo *philo);
void *life(void *args);
ssize_t	start_philo(t_philo *philo);


#endif