/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:32:17 by mmarinov          #+#    #+#             */
/*   Updated: 2024/10/08 16:18:53 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	free_memory_bonus(char **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

static char	*extract_line_bonus(char **buffer)
{
	size_t	i;
	char	*line;
	char	*new_buffer;

	if (!buffer || !*buffer)
		return (NULL);
	i = 0;
	while ((*buffer)[i] && (*buffer)[i] != '\n')
		i++;
	if ((*buffer)[i] == '\n')
		i++;
	line = ft_strndup_bonus(*buffer, i);
	if (!line)
		return (NULL);
	new_buffer = ft_strdup_bonus(*buffer + i);
	free_memory_bonus(buffer);
	if (!new_buffer)
	{
		free(line);
		return (NULL);
	}
	*buffer = new_buffer;
/*	if (*buffer && **buffer == '\0')
		free_memory(buffer);
		*/
	return (line);
}

static int	read_from_file_bonus(int fd, char **buffer)
{
	char	*read_buf;
	char	*temp;
	ssize_t	bytes_read;

	read_buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!read_buf)
		return (-1);
	bytes_read = read(fd, read_buf, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		free(read_buf);
		return (-1);
	}
	if (bytes_read == 0)
	{
		free(read_buf);
		return (0);

	}
	read_buf[bytes_read] = '\0';
	if (*buffer)
	{
		temp = ft_strjoin_bonus(*buffer, read_buf);
		free(read_buf);
		if (!temp)
			return (-1);
		free_memory_bonus(buffer);
		*buffer = temp;
	}
	else
	{
		*buffer = ft_strdup_bonus(read_buf);
		free(read_buf);
		if (!*buffer)
			return (-1);
	}
	return (bytes_read);
}

char	*get_next_line_bonus(int fd)
{
	char		*line;
	static char	*buffer[MAX_FILES];
	ssize_t		b_read;

	b_read = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 2147483647)
		return (NULL);
	if (!buffer[fd])
		buffer[fd] = ft_strdup_bonus("");
	while (buffer[fd] && !ft_strchr_bonus(buffer[fd], '\n'))
	{
		b_read = read_from_file_bonus(fd, &buffer[fd]);
		if (b_read <= 0)
			return (free_memory_bonus(&buffer[fd]), NULL);
	}
	if (b_read == 0 && (!buffer[fd] || *buffer[fd] == '\0'))
	{
		free_memory_bonus(&buffer[fd]);
		return (NULL);
	}
	line = extract_line_bonus(&buffer[fd]);
	return (line);
}
