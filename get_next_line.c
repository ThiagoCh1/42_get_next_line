/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thribeir <thribeir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:58:38 by thribeir          #+#    #+#             */
/*   Updated: 2025/10/19 17:05:56 by thribeir         ###   ########.fr       */
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
	char	*line;
	size_t	i;
	size_t	j;

	if (stash == NULL || stash[0] == '\0')
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
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
	char	*nl;
	char	*res;
	size_t	len;

	nl = gnl_strchr(stash, '\n');
	if ((nl == NULL || *(nl + 1) == '\0') && stash)
	{
		free(stash);
		return (NULL);
	}
	nl++;
	len = gnl_strlen(nl);
	res = malloc(len + 1);
	if (res == NULL)
	{
		free(stash);
		return (NULL);
	}
	ft_strlcpy(res, nl, len + 1);
	free(stash);
	return (res);
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
	if (line == NULL)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
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
