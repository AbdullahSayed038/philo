#include "philo.h"

void sleep_the_action2(int time_in_ms, t_philosopher *philosopher, t_input *input)
{
	int	remaining_time;
	int	interval;

	remaining_time = time_in_ms * 1000;
	while (remaining_time > 0)
	{
		if (remaining_time >= 12000)
			interval = 12000;
		else
			interval = remaining_time;
		usleep(interval);
		remaining_time -= interval;
		if (time_taken(philosopher, input) != 0)
		{
			set_death(input, philosopher, philosopher->id);
			return;
		}
	}
}

void sleep_the_action(int time_in_ms, t_philosopher *philosopher, t_input *input)
{
	int	remaining_time;
	int	interval;

	remaining_time = time_in_ms * 1000;
	while (remaining_time > 0)
	{
		if (remaining_time >= 5000)
			interval = 5000;
		else
			interval = remaining_time;
		usleep(interval);
		remaining_time -= interval;
		if (time_taken(philosopher, input) != 0)
		{
			set_death(input, philosopher, philosopher->id);
			return;
		}
	}
}

void	action(t_input *philo, t_philosopher *philosopher, int nb, const char *str)
{
	ssize_t	time;

	(void)philosopher;
	time = get_current_program_time(philo);
	pthread_mutex_lock(&philo->printing);
	printf("%zi Philosopher %i is %s.\n", time, nb, str);
	pthread_mutex_unlock(&philo->printing);
}

int	any_death(t_input *input)
{
	if (input->dead != 0)
		return (0);
	return (1);
}

void	eat(t_philosopher *philosopher, t_input *input, int index)
{
	pthread_mutex_lock(&input->fork[philosopher->left_fork]);
	action(input, philosopher, index + 1, "has taken a fork");
	pthread_mutex_lock(&input->fork[philosopher->right_fork]);
	action(input, philosopher, index + 1, "has taken a fork");
	action(input, philosopher, index + 1, "is eating");
	philosopher->meals_had++;
	philosopher->time_of_last_meal = get_current_program_time(input);
	sleep_the_action(input->time_to_eat, philosopher, input);
	if (time_taken(philosopher, input) != 0)
	{
		set_death(input, philosopher, index);
		return ;
	}
	pthread_mutex_unlock(&input->fork[philosopher->left_fork]);
	pthread_mutex_unlock(&input->fork[philosopher->right_fork]);
}