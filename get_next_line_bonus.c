/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmattion <jmattion@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:27:07 by jmattion          #+#    #+#             */
/*   Updated: 2025/11/12 16:12:39 by jmattion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*free_join(char *s1, char *s2)
{
	char	*dest;

	dest = ft_strjoin(s1, s2);
	free(s1);
	return (dest);
}

char	*read_line(int fd, char *dest)
{
	int		byte;
	char	*buffer;

	byte = 1;
	if (!dest)
		dest = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	while (byte > 0)
	{
		byte = read(fd, buffer, BUFFER_SIZE);
		if (byte < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[byte] = '\0';
		if (byte == 0)
			break ;
		dest = free_join(dest, buffer);
		if (ft_strchr(dest, '\n'))
			break ;
	}
	free(buffer);
	return (dest);
}

char	*trim_line(char *buffer)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	dest = ft_calloc(i + 2, sizeof(char));
	while (j <= i && buffer[j])
	{
		dest[j] = buffer[j];
		j++;
	}
	return (dest);
}

char	*next_line(char *buffer)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	dest = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	if (!dest)
		return (NULL);
	i++;
	while (buffer[i + j])
	{
		dest[j] = buffer[i + j];
		j++;
	}
	free(buffer);
	return (dest);
}

char	*get_next_line(int fd)
{
	static char	*buffer[256];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer[fd] = read_line(fd, buffer[fd]);
	if (!buffer[fd])
	{
		return (NULL);
	}
	line = trim_line(buffer[fd]);
	buffer[fd] = next_line(buffer[fd]);
	return (line);
}
