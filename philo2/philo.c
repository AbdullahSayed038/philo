#include "philo.h"

ssize_t	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while(str[i])
		i++;
	return (i);
}

void	exitfree(t_philo *philo, char *msg, int fd, int exit_code)
{
	(void)philo;
	if (msg)
		write(fd, msg, ft_strlen(msg));
	exit (exit_code);
}

int	ft_atoi_philo(char *str)
{
	long long	nb;
	int			i;

	if (!str)
		return (-1);
	nb = 0;
	i = 0;
	while ((str[i] == ' ' || str[i] == '\t' || str[i] == '\n') && str[i])
		i++;
	if (str[i] == '-')
		return (-1);
	else if (str[i] == '+')
		i++;
	while (*str)
	{
		if ((str[i] >= '0' && str[i] <= '9') && nb <= 2147483647)
			nb = nb * 10 + (str[i] - '0');
		else
			break;
		i++;
	}
	if (nb > 2147483647)
		return (-1);
	return (nb);
}

void	initialize_philosophers(t_philo *philo)
{
	int	nb_of_philo;
	int	i;

	i = philo->nb_of_philos - 1;
	nb_of_philo = philo->nb_of_philos;
	while (i >= 0)
	{
		philo->philosopher[i].id = i;
		philo->philosopher[i].last_meal = philo->start_time;
		philo->philosopher[i].left_fork = i;
		philo->philosopher[i].right_fork = (i + 1) % nb_of_philo;
		philo->philosopher[i].meals = 0;
		i--;
	}
}

ssize_t	initialize_mutex_locks(t_philo *philo)
{
	int	i;

	i = philo->nb_of_philos - 1;
	while (i >= 0)
	{
		if (pthread_mutex_init(&(philo->fork[i]), NULL))
			return (-1);
		i--;
	}
	if (pthread_mutex_init(&(philo->meal_counter), NULL))
		return (1);
	if (pthread_mutex_init(&(philo->printing), NULL))
		return (1);
	return (0);
}

void	initialize_philo(t_philo *philo, char **av)
{
	philo->start_time = get_current_time();
	philo->dead = 0;
	philo->meals = 0;
	philo->satisfaction = -1;
	philo->nb_of_philos = ft_atoi_philo(av[1]);
	philo->time_to_die = ft_atoi_philo(av[2]);
	philo->time_to_eat = ft_atoi_philo(av[3]);
	philo->time_to_sleep = ft_atoi_philo(av[4]);
	if (philo->nb_of_philos < 2 || philo->time_to_die < 0 || philo->time_to_eat < 0 || philo->time_to_sleep < 0 || philo->nb_of_philos > 250)
		exitfree(philo, "Invalid Values\n", 2, 1);
	initialize_mutex_locks(philo);
	initialize_philosophers(philo);
	return ;
}

void 	set_death(t_philo *philo, t_philosopher *philosopher, size_t index)
{
	pthread_mutex_lock(&philo->death_checker);
	if (philo->dead == 0)
	{
		philo->dead = 1;
		action(philo, philosopher, index + 1, "has died");
	}
	pthread_mutex_unlock(&philo->death_checker);
}

void	sleep_the_action(int time)
{
	usleep(time * 1000);
}


ssize_t get_current_time(void)
{
    struct	timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

ssize_t	get_current_program_time(t_philo *philo)
{
	ssize_t	current_time;

	current_time = (get_current_time() - philo->start_time);
	return (current_time);
}

ssize_t check_all_satisfaction(t_philo *philo)
{
	int	i;

	i = 0;
	while(i < philo->nb_of_philos)
	{
		if (philo->philosopher->meals == philo->satisfaction) 
			i++;
		else
			return (1);
	}
	return (0);
}

ssize_t time_taken(t_philosopher *philosopher, t_philo *philo)
{
	ssize_t time;
	
	time = get_current_program_time(philo);
	if (time - philosopher->last_meal > philo->time_to_die)
		return 1;
	return 0;
}

void	eating(t_philosopher	*philosopher, t_philo *philo, int index)
{
	while (philosopher->left_fork != 1 && philosopher->right_fork != 1)
	{
		if (philosopher->left_fork != 1)
		{
			pthread_mutex_lock(&philo->fork[philosopher->left_fork]);
			philosopher->left_fork = 1;
			action(philo, philosopher, index + 1, "has taken left fork");
		}
		if (philosopher->right_fork != 1)
		{
			philosopher->right_fork = 1;
			pthread_mutex_lock(&philo->fork[philosopher->right_fork]);
			action(philo, philosopher, index + 1, "has taken right fork");
		}
	}
	if (time_taken(philosopher, philo) != 0)
	{
		set_death(philo, philosopher, index);
		return ;
	}
	action(philo, philosopher, index + 1, "is eating");
	philosopher->last_meal = get_current_program_time(philo);
	sleep_the_action(philo->time_to_eat);
	philosopher->meals++;
	if (time_taken(philosopher, philo) != 0)
	{
		set_death(philo, philosopher, index);
		return ;
	}
	pthread_mutex_unlock(&philo->fork[philosopher->left_fork]);
	pthread_mutex_unlock(&philo->fork[philosopher->right_fork]);
}

void	sleeping(t_philosopher	*philosopher, t_philo *philo, int index)
{
	if (time_taken(philosopher, philo) != 0)
	{
		set_death(philo, philosopher, index);
		return ;
	}
	action(philo, philosopher, index + 1, "sleeping");
	sleep_the_action(philo->time_to_sleep);
	if (time_taken(philosopher, philo) != 0)
	{
		set_death(philo, philosopher, index);
		return ;
	}
}

void	thinking(t_philosopher	*philosopher, t_philo *philo, int index)
{
	if (time_taken(philosopher, philo) != 0)
	{
		set_death(philo, philosopher, index);
		return ;
	}
	action(philo, philosopher, index + 1, "is thinking");
}

void	action(t_philo *philo, t_philosopher *philosopher, int nb, const char *str)
{
	ssize_t	time;

	(void)philosopher;
	time = get_current_program_time(philo);
	if (death_alarm(philo) == 0)
		return;
	pthread_mutex_lock(&philo->printing);
	printf("%zi      Philosopher %i is %s.\n", time, nb, str);
	pthread_mutex_unlock(&philo->printing);
}

ssize_t	death_alarm(t_philo *philo)
{
	if (!philo)
		return (-1);
	pthread_mutex_lock(&philo->death_checker);
	if (philo->dead != 0)
	{
		pthread_mutex_unlock(&philo->death_checker);
		return (1);
	}
	pthread_mutex_unlock(&philo->death_checker);
	return (0);
}

void *life(void *args)
{
	t_life_args *life_args = (t_life_args *)args;
	t_philosopher *philosopher = life_args->philosopher;
	t_philo *philo = life_args->philo;
	int index = life_args->index;

	while (death_alarm(philo) == 0 && (philo->satisfaction != -1 || philosopher->meals != philo->satisfaction))
	{
		if (death_alarm(philo) != 0)
			return NULL;
		eating(philosopher, philo, index);
		if (death_alarm(philo) != 0)
			return NULL;
		sleeping(philosopher, philo, index);
		if (death_alarm(philo) != 0)
			return NULL;
		thinking(philosopher, philo, index);
	}
	return NULL;
}

ssize_t start_philo(t_philo *philo)
{
	int i;
	t_life_args *args;

	i = 0;
	while (i < philo->nb_of_philos)
	{
		args = malloc(sizeof(t_life_args));
		if (!args)
			return (-1);
		args->philosopher = &philo->philosopher[i];
		args->philo = philo;
		args->index = i;
		if (pthread_create(&(philo->philosopher[i].thread_id), NULL, life, args) != 0)
		{
			free(args);
			return (-1);
		}
		i++;
	}
	i = 0;
	while (i < philo->nb_of_philos)
	{
		if (pthread_join(philo->philosopher[i].thread_id, NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}


int main(int ac, char **av)
{
	t_philo	philo;

	if (ac != 5 && ac != 6)
		exitfree(&philo, "Invalid Arguments\n", 2, 1);
	initialize_philo(&philo, av);
	if (ac == 6)
	{
		philo.meals = ft_atoi_philo(av[5]);
		if (philo.meals <= 0)
			exitfree(&philo, "No meals? :(\n", 2, 1);
	}
	if (start_philo(&philo) != 0)
	{
		exitfree(&philo, "rip", 2, 1);
	}
	return (0);
}
