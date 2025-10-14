#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

/* your function */
char *get_next_line(int fd);

/* show characters visibly (prints '\n' as "\\n") */
static void print_visible(const char *s)
{
	size_t i = 0;

	while (s[i])
	{
		if (s[i] == '\n')
			printf("\\n");
		else
			putchar(s[i]);
		i++;
	}
}

int main(int argc, char **argv)
{
	const char *path = (argc > 1) ? argv[1] : "multiple_nl.txt";
	int fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return 1;
	}

	printf("Testing file: %s\n", path);
#ifdef BUFFER_SIZE
	printf("BUFFER_SIZE = %d\n", BUFFER_SIZE);
#endif

	int i = 1;
	char *line;
	while ((line = get_next_line(fd)) != NULL)
	{
		size_t len = strlen(line);
		printf("[%d] len=%zu: \"", i++, len);
		print_visible(line);
		printf("\"\n");
		free(line);
	}

	/* NULL-after-EOF check */
	line = get_next_line(fd);
	printf("After EOF call -> %s\n", line == NULL ? "NULL (OK)" : "NOT NULL (BUG)");
	free(line); /* safe if NULL */

	close(fd);
	return 0;
}
