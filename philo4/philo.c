#include "philo.h"

ssize_t get_current_time(void)
{
	struct	timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void 	set_death(t_input *philo, t_philosopher *philosopher, size_t index)
{
	pthread_mutex_lock(&philo->check_death);
	if (philo->dead == 0)
	{
		philo->dead = 1;
		action(philo, philosopher, index + 1, "has died");
	}
	pthread_mutex_unlock(&philo->check_death);
}

void	ft_bzero(void *s, size_t n)
{
	if (!s)
		return (perror("bzero: sending null"));
	while (n--)
		*(unsigned char *)s++ = 0;
}

int main(int ac, char **av)
{
	t_input input;

	if (ac != 5 && ac != 6)
		return (-1);
	if (init_input(&input, av, ac) != 0)
		return (-1);
	if (init_philo(&input) != 0)
		return (-1);
	if (init_mutexlocks(&input) != 0)
		return (-1);
	if (input.food_flag == 0)
	{
		if (philo_no_stop(&input) != 0)
			free_all(&input);
	}
	else
	{
		if (philo_with_stop(&input) != 0)
			return (-1);
	}
	return (0);
}
