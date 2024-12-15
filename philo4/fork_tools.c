/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsayed <abdsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 19:08:33 by abdsayed          #+#    #+#             */
/*   Updated: 2024/12/15 20:00:11 by abdsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	grab_fork(t_philosopher *philosopher, t_input *input)
{
	while (any_death(input) == false)
	{
		if (time_taken(philosopher, input) == true)
			set_death(input, philosopher, philosopher->id);
		pthread_mutex_lock(&input->fork[philosopher->left_fork]);
		if (input->fork_check[philosopher->left_fork] == 0)
		{
			input->fork_check[philosopher->left_fork] = 1;
			pthread_mutex_unlock(&input->fork[philosopher->left_fork]);
			break ;
		}
		pthread_mutex_unlock(&input->fork[philosopher->left_fork]);
		usleep(100);
	}
}

void	grab_second_fork(t_philosopher *philosopher, t_input *input)
{
	while (any_death(input) == false)
	{
		if (time_taken(philosopher, input) == true)
			set_death(input, philosopher, philosopher->id);
		pthread_mutex_lock(&input->fork[philosopher->right_fork]);
		if (input->fork_check[philosopher->right_fork] == 0)
		{
			input->fork_check[philosopher->right_fork] = 1;
			pthread_mutex_unlock(&input->fork[philosopher->right_fork]);
			break ;
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
