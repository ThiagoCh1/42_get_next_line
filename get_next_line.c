/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thribeir <thribeir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:58:38 by thribeir          #+#    #+#             */
/*   Updated: 2025/10/14 05:05:15 by thribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_to_stash(int fd, char *stash)
{
	ssize_t	nread;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	while (!gnl_strchr(stash, '\n'))
	{
		nread = read(fd, buf, BUFFER_SIZE);
		if (nread <= 0)
		{
			free(buf);
			if (nread == -1 || !stash || !stash[0])
			{
				free(stash);
				return (NULL);
			}
			return (stash);
		}
		buf[nread] = '\0';
		stash = gnl_strjoin(stash, buf);
	}
	free(buf);
	return (stash);
}

char	*get_linee(char *stash)
{
	char		*line;
	size_t		i;
	size_t		j;

	i = 0;
	while (stash[i])
	{
		if (stash[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	line = malloc(i + 1);
	if (line == NULL)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = stash[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*new_stash(char *stash)
{
	char	*new_stash;
	char	*new_pos;
	size_t	i;

	new_pos = gnl_strchr(stash, '\n');
	if (new_pos == NULL)
	{
		free(stash);
		return (NULL);
	}
	new_pos += 1;
	new_stash = malloc(gnl_strlen(new_pos) + 1);
	if (new_stash == NULL)
	{
		free(stash);
		return (NULL);
	}
	i = -1;
	while (++i < gnl_strlen(new_pos))
		new_stash[i] = new_pos[i];
	new_stash[i] = '\0';
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_to_stash(fd, stash);
	if (stash == NULL)
		return (NULL);
	line = get_linee(stash);
	stash = new_stash(stash);
	return (line);
}

/*#include <stdio.h>

int main(int argc, char **argv)
{
    int   fd;
    char *line;
    int   i = 1;

    if (argc == 2)
    {
        fd = open(argv[1], O_RDONLY);
        if (fd < 0)
        {
            perror("open");
            return (1);
        }
    }
    else
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return (1);
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Line %d: %s", i++, line);
        free(line);
    }

    close(fd);
    return (0);
}
*/
