#include "philo.h"

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
			return (-1);
	}
	else
	{
		if (philo_with_stop(&input) != 0)
			return (-1);
	}
	return (0);
}
