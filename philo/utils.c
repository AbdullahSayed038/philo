/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsayed <abdsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 13:28:35 by abdsayed          #+#    #+#             */
/*   Updated: 2024/10/21 14:10:54 by abdsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}



void	ft_putendl_fd(const char *const s, int fd)
{
	if (!s)
		return (perror("putendl_fd: sending null"));
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

void	ft_putstr_fd(const char *const s, int fd)
{
	if (!s)
		return (perror("putstr_fd: sending null"));
	if (write(fd, s, ft_strlen(s)) < 0)
		perror("putstr_fd: write error");
}

void	ft_putchar_fd(char c, int fd)
{
	if (write(fd, &c, 1) < 0)
		perror("ft_putchar_fd: write error");
}

void	*safe_malloc(size_t bytes)
{
	void	*malloced_buffer;

	if (bytes > 0x7fffffff)
		put_fd_nl("Malloc Error", 2);
	malloced_buffer = malloc(bytes + (size_t)1 + (size_t)7 * (bytes % sizeof(void *) == 0));
	if (!malloced_buffer)
		return (NULL);
	if (!malloced_buffer)
		return (NULL);
	ft_bzero(malloced_buffer, bytes + (size_t)1 + (size_t)7 * (bytes % sizeof(void *) == 0));
	return (malloced_buffer);
}

static bool	valid_atoi(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (perror("strict atoi: sending null"), false);
	if (str <= (const char *)0x00100000)
		return (perror("strict atoi: invalid pointer"), false);
	if (!*str)
		return (perror("strict atoi: empty string"), false);
	while (str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while (str[i] == ' ')
		i++;
	return (!str[i]);
}

int	ft_atoi(const char *str)
{
	int					i;
	int					neg;
	signed long long	res;

	i = 0;
	res = 0;
	neg = 1;
	if (!valid_atoi(str))
		return (-1);
	while (str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		neg = 44 - str[i++];
	while (str[i] == '0')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (str[i++] - '0') + (res * 10);
		if ((neg == 1 && res > 0x7fffffffLL)
			|| (neg == -1 && res > 0x80000000LL))
			return (perror("strict atoi: overflow"), -1);
	}
	return ((int)(res * neg));
}


ssize_t m_sleep(const size_t time)
{
	usleep(time * 1000);
	return (0);
}