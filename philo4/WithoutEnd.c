/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WithoutEnd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsayed <abdsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:56:10 by abdsayed          #+#    #+#             */
/*   Updated: 2024/12/15 19:59:46 by abdsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_func(void	*args)
{
	t_life_args		*life_args;
	t_philosopher	*philosopher;
	t_input			*input;
	int				index;

	life_args = (t_life_args *)args;
	philosopher = life_args->philosopher;
	input = life_args->input;
	index = life_args->index;
	while (any_death(input) == false)
	{
		eat(philosopher, input, index);
		if (any_death(input) == true)
			break ;
		action(input, index + 1, "is sleeping");
		msleep(input, input->time_to_sleep, philosopher);
		if (time_taken(philosopher, input) == true)
			set_death(input, philosopher, index);
		if (any_death(input) == true)
			break ;
		action(input, index + 1, "is thinking");
	}
	return (NULL);
}

void	join_threads(t_input *input)
{
	int	i;

	i = 0;
	while (i < input->nb_of_philo)
	{
		if (pthread_join(input->philosophers[i].thread_id, NULL) != 0)
			return ;
		i++;
	}
}

int	philo_no_stop(t_input *input)
{
	int			i;
	t_life_args	*args;

	i = 0;
	while (i < input->nb_of_philo)
	{
		usleep(1000 * (i % 2));
		args = malloc(sizeof(t_life_args));
		if (!args)
			return (-1);
		args->philosopher = &input->philosophers[i];
		args->input = input;
		args->index = i;
		if (pthread_create(&(input->philosophers[i].thread_id), \
			NULL, philo_func, args) != 0)
		{
			free(args);
			return (-1);
		}
		i++;
	}
	join_threads(input);
	return (0);
}
