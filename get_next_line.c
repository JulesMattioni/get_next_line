#include "get_next_line.h"

char	*free_join(char *s1, char *s2)
{
	char *dest;

	dest = ft_strjoin(s1, s2);
	free(s1);
	return (dest);
}

char	*read_line(int fd, char *dest)
{
	int	byte;
	char *buffer;

	byte = 1;
	if (!dest)
		dest = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	while (byte > 0)
	{
		byte = read(fd, buffer, BUFFER_SIZE);
		if (byte == -1)
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

char	*trim_line(char *buffer)
{
	int i;
	int j;
	char *dest;

	i = 0;
	j = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	dest = ft_calloc(i + 2, sizeof(char));
	if (!dest)
		return (NULL);
	while (j <= i)
	{
		dest[j] = buffer[j];
		j++;
	}
	return (dest);
}

char	*next_line(char *buffer)
{
	int i;
	int j;
	char *dest;

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
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = read_line(fd, buffer);
	if (!buffer)
		return (NULL);
	line = trim_line(buffer);
	buffer = next_line(buffer);
	return (line);
}
