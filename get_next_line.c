/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmattion <jmattion@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:04:07 by jmattion          #+#    #+#             */
/*   Updated: 2025/11/05 14:08:11 by jmattion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

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
		dest = free_join(dest, buffer);
		if (ft_strchr(dest, '\n'))
			break ;
	}
	free(buffer);
	return (dest);
}

char	**split_line(char *buffer)
{
	int		i;
	int		j;
	char	**dest;

	i = 0;
	j = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	dest = ft_calloc(2, sizeof(char *));
	dest[0] = ft_calloc(i + 2, sizeof(char));
	dest[1] = ft_calloc((ft_strlen(buffer) - i) + 1, sizeof(char));
	while (j <= i && buffer[j])
	{
		dest[0][j] = buffer[j];
		j++;
	}
	i = 0;
	while (buffer[j + i])
	{
		dest[1][i] = buffer[j + i];
		i++;
	}
	return (dest);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	char		**split;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = read_line(fd, buffer);
	if (!buffer || !buffer[0])
		return (NULL);
	split = split_line(buffer);
	free(buffer);
	line = ft_strdup(split[0]);
	buffer = ft_strdup(split[1]);
	free(split);
	return (line);
}
