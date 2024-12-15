/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WithEnd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsayed <abdsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:56:14 by abdsayed          #+#    #+#             */
/*   Updated: 2024/12/15 22:27:47 by abdsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_func_2(void	*args)
{
	t_life_args		*life_args;
	t_philosopher	*philosopher;
	t_input			*input;

	life_args = (t_life_args *)args;
	philosopher = life_args->philosopher;
	input = life_args->input;
	while ((any_death(input) == false) && \
		(philosopher->meals_had != input->meals))
	{
		eat(philosopher, input, philosopher->id);
		if (any_death(input) == true || \
			philosopher->meals_had == input->meals)
			break ;
		action(input, philosopher->id + 1, "is sleeping");
		msleep(input, input->time_to_sleep, philosopher);
		if (time_taken(philosopher, input) == true)
			set_death(input, philosopher, philosopher->id);
		if (any_death(input) == true)
			break ;
		action(input, philosopher->id + 1, "is thinking");
	}
	free(args);
	return (NULL);
}

int	philo_with_stop(t_input *input)
{
	int			i;
	t_life_args	*args;

	i = 0;
	args = NULL;
	while (i < input->nb_of_philo)
	{
		if (i % 2 != 0)
			usleep(1000);
		args = safe_malloc(sizeof(t_life_args));
		if (!args)
			return (-1);
		args->philosopher = &input->philosophers[i];
		args->input = input;
		args->index = i;
		if (pthread_create(&(input->philosophers[i].thread_id), NULL, \
			philo_func_2, args) != 0)
		{
			free(args);
			return (-1);
		}
		i++;
	}
	join_threads(input);
	return (0);
}
