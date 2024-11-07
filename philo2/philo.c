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
		if ((str[i] >= '0' && str[i] <= '9') && nb <= INT_MAX)
			nb = nb * 10 + (str[i] - '0');
		else
			break;
		i++;
	}
	if (nb > INT_MAX)
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
		philo->philosopher[i].last_meal = 0;
		philo->philosopher[i].left_fork = i;
		philo->philosopher[i].right_fork = (i + 1) % nb_of_philo;
		philo->philosopher[i].meals = 0;
		philo->philosopher[i].philo_set = philo;
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

ssize_t check_all_satisfaction(t_philo *philo)
{
	
}

void	*eating(t_philosopher	*philosopher)
{

}

void	*sleeping(t_philosopher	*philosopher)
{

}

void	*thinking(t_philosopher	*philosopher)
{

}

void	action(t_philo *philo, t_philosopher	*philosopher)
{

}

ssize_t	start_philo(t_philo *philo)
{
	int	i;

	i = 0;
	while(check_all_satisfaction(philo) == 0)
	{
		i = 0;
		while (i < philo->nb_of_philos)
		{
			if (pthread_create(&(philo->philosopher[i].thread_id), NULL, eating(&(philo->philosopher[i])), NULL) != 0)
				return (-1);
			if (pthread_create(&(philo->philosopher[i].thread_id), NULL, sleeping(&(philo->philosopher[i])), NULL) != 0)
				return (-1);
			if (pthread_create(&(philo->philosopher[i].thread_id), NULL, thinking(&(philo->philosopher[i])), NULL) != 0)
				return (-1);
			i++;
		}
	}
}

int main(int ac, char **av)
{
	t_philo	philo;

	if (ac != 5 && ac != 6)
		exitfree(&philo, "Invalid Arguments\n", 2, 1);
	initialize_philo(&philo, av);
	if (ac == 6)
	{
		philo.satisfaction = ft_atoi_philo(av[5]);
		if (philo.satisfaction <= 0)
			exitfree(&philo, "No meals? :(\n", 2, 1);
	}
	if (start_philo(&philo) != 0)
	{

	}
}
