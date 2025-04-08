/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:19:59 by htharrau          #+#    #+#             */
/*   Updated: 2025/02/19 15:46:47 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*get_next_line(int fd);
static char	*ft_stash(char *buffer, char **stash);
static char	*ft_line(char **stash);
static int	ft_read(int fd, char **stash);
static char	*ft_remain(char **stash);

static char	*ft_stash(char *buffer, char **stash)
{
	char	*temp;

	if (!*stash)
		return (ft_strdup(buffer));
	temp = ft_strjoin(*stash, buffer);
	free(*stash);
	if (temp == NULL)
		return (NULL);
	*stash = temp;
	return (*stash);
}

static char	*ft_line(char **stash)
{
	char	*temp;
	char	*line;
	char	*newline_ptr;

	if (!*stash)
		return (NULL);
	newline_ptr = ft_strchr(*stash, '\n');
	if (newline_ptr)
	{
		*newline_ptr = '\0';
		line = ft_strjoin(*stash, "\n");
		temp = ft_strdup(newline_ptr + 1);
		free(*stash);
		*stash = temp;
		return (line);
	}
	return (NULL);
}

static int	ft_read(int fd, char **stash)
{
	char		*buffer;
	ssize_t		bytes_read;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (-1);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		free(buffer);
		return (-1);
	}
	buffer[bytes_read] = '\0';
	*stash = ft_stash(buffer, stash);
	free(buffer);
	return (bytes_read);
}

static char	*ft_remain(char **stash)
{
	char	*line;

	if (*stash && **stash)
	{
		line = ft_strdup(*stash);
		free(*stash);
		*stash = NULL;
		return (line);
	}
	else
	{
		free(*stash);
		*stash = NULL;
		return (NULL);
	}
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	ssize_t		bytes_read;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1 || fd >= 1024)
	{
			cleanup_stash(&stash[fd]);
			return NULL;
	}
	while (1)
	{
		line = ft_line(&stash[fd]);
		if (line)
			return (line);
		bytes_read = ft_read(fd, &stash[fd]);
		if (bytes_read < 0)
		{
			free(stash[fd]);
			stash[fd] = NULL;
			return (NULL);
		}
		if (bytes_read == 0)
			return (ft_remain(&stash[fd]));
	}
}

// Cleanup all stashes when called with invalid fd
void	cleanup_stash(char	*stash[])
{
	int	i;

	i = 0;
	while (i < 1024)
	{
		if (stash[i])
		{
			free(stash[i]);
			stash[i] = NULL;
		}
		i++;
	}
}