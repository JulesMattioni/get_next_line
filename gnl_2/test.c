#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int main(void)
{
    char *line;
    int fd;

    fd = open("txt", O_RDONLY);
    line = get_next_line(fd);
    printf("%s", line);
    free(line);
    line = get_next_line(fd);
    printf("%s", line);
    free(line);
    line = get_next_line(fd);
    printf("%s", line);
    free(line);
    close(fd);
}