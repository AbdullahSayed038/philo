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
	while (str[i])
	{
		while ((str[i] == ' ' || str[i] == '\t' || str[i] == '\n') && str[i])
			i++;
		if (str[i] == '-')
			return (-1);
		else if (str[i] == '+')
			i++;
		while (*str)
		{
			if (str[i] >= '0' && str[i] <= '9')
				nb = nb * 10 + (str[i] - '0');
			else
				break;
			i++;
		}
	}
}

void	initialize_philo(t_philo *philo, char **av)
{
	philo->dead = 0;
	philo->fork = ;
	philo->meals = ;
	philo->nb_of_philos = ;
	philo->philosopher = ;
	philo->satisfaction = ;
	philo->start_time = ;
	philo->time_to_die = ;
	philo->time_to_eat = ;
	philo->time_to_sleep = ;
}

int main(int ac, char **av)
{
	t_philo	philo;

	if (ac != 5 && ac != 6)
		exitfree(&philo, "Invalid Arguments\n", 2, 1);
	initialize_philo(&philo, av);
	
}