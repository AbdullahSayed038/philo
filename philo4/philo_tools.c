
#include "philo.h"

void	msleep(t_input *input, size_t ms)
{
	size_t	start;

	start = get_current_program_time(input);
	while (any_death(input) == false && ((get_current_program_time(input) - start) < ms))
		usleep(100);
}

void	action(t_input *philo, t_philosopher *philosopher, int nb, const char *str)
{
	ssize_t	time;

	(void)philosopher;
	time = get_current_program_time(philo);
	pthread_mutex_lock(&philo->printing);
	printf("%zi %i %s\n", time, nb, str);
	pthread_mutex_unlock(&philo->printing);
}

int	any_death(t_input *input)
{
	pthread_mutex_lock(&input->check_death);
	if (input->dead != 0)
	{
		pthread_mutex_unlock(&input->check_death);
		return (true);
	}
	pthread_mutex_unlock(&input->check_death);
	return (false);
}

void	grab_fork(t_philosopher *philosopher, t_input *input)
{
	while (any_death(input) == false)
	{
		pthread_mutex_lock(&input->fork[philosopher->left_fork]);
		if (input->fork_check[philosopher->left_fork] == 0)
		{
			input->fork_check[philosopher->left_fork] = 1;
			pthread_mutex_unlock(&input->fork[philosopher->left_fork]);
			break;
		}
		pthread_mutex_unlock(&input->fork[philosopher->left_fork]);
		usleep(100);
	}
}

void	grab_second_fork(t_philosopher *philosopher, t_input *input)
{
	while (any_death(input) == false)
	{
		pthread_mutex_lock(&input->fork[philosopher->right_fork]);
		if (input->fork_check[philosopher->right_fork] == 0)
		{
			input->fork_check[philosopher->right_fork] = 1;
			pthread_mutex_unlock(&input->fork[philosopher->right_fork]);
			break;
		}
		pthread_mutex_unlock(&input->fork[philosopher->right_fork]);
		usleep(100);
	}
}

void	release_fork(t_input *input, t_philosopher *philosopher)
{
	pthread_mutex_lock(&input->fork[philosopher->left_fork]);
	input->fork_check[philosopher->left_fork] = 0;
	pthread_mutex_unlock(&input->fork[philosopher->left_fork]);
}

void	release_second_fork(t_input *input, t_philosopher *philosopher)
{
	pthread_mutex_lock(&input->fork[philosopher->right_fork]);
	input->fork_check[philosopher->right_fork] = 0;
	pthread_mutex_unlock(&input->fork[philosopher->right_fork]);
}

void	release_both_forks(t_input *input, t_philosopher *philosopher)
{
	release_fork(input, philosopher);
	release_second_fork(input, philosopher);
}

void	eat(t_philosopher *philosopher, t_input *input, int index)
{
	if (any_death(input) == true)
		return ;
	if (index % 2 == 0)
	{
		grab_second_fork(philosopher, input);
		grab_fork(philosopher, input);
	}
	else
	{
		grab_fork(philosopher, input);
		grab_second_fork(philosopher, input);
	}
	if (any_death(input) == true)
	{
		release_both_forks(input, philosopher);
		return ;
	}
	action(input, philosopher, index + 1, "has taken a fork");
	action(input, philosopher, index + 1, "has taken a fork");
	action(input, philosopher, index + 1, "is eating");
	philosopher->meals_had++;
	philosopher->time_of_last_meal = get_current_program_time(input);
	msleep(input, input->time_to_eat);
	if (time_taken(philosopher, input) == true)
		set_death(input, philosopher, index);
	release_both_forks(input, philosopher);
}
