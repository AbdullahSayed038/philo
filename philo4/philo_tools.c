/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsayed <abdsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:56:22 by abdsayed          #+#    #+#             */
/*   Updated: 2024/12/15 19:59:21 by abdsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	msleep(t_input *input, size_t ms, t_philosopher *philosopher)
{
	size_t	start;

	start = get_current_program_time(input);
	while (any_death(input) == false && \
		((get_current_program_time(input) - start) < ms))
		{
			if (time_taken(philosopher, input) == true)
				set_death(input, philosopher, philosopher->id);
			usleep(100);
		}
}

void	action(t_input *philo, int nb, const char *str)
{
	ssize_t	time;

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

void	eat(t_philosopher *philosopher, t_input *input, int index)
{
	if (any_death(input) == true)
		return ;
	if (index % 2 == 0)
		(grab_second_fork(philosopher, input), grab_fork(philosopher, input));
	else
		(grab_fork(philosopher, input), grab_second_fork(philosopher, input));
	if (any_death(input) == true)
	{
		release_both_forks(input, philosopher);
		return ;
	}
	action(input, index + 1, "has taken a fork");
	action(input, index + 1, "has taken a fork");
	if (time_taken(philosopher, input) == true)
		set_death(input, philosopher, index);
	if (any_death(input) == true)
	{
		release_both_forks(input, philosopher);
		return ;
	}
	action(input, index + 1, "is eating");
	philosopher->meals_had++;
	philosopher->time_of_last_meal = get_current_program_time(input);
	msleep(input, input->time_to_eat, philosopher);
	if (time_taken(philosopher, input) == true)
		set_death(input, philosopher, index);
	release_both_forks(input, philosopher);
}
