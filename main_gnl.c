#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

/* your function under test */
char *get_next_line(int fd);

/* print string with visible newlines */
static void print_visible(const char *s)
{
    size_t i = 0;
    while (s[i] != '\0')
    {
        if (s[i] == '\n')
            fputs("\\n", stdout);
        else
            fputc(s[i], stdout);
        i++;
    }
}

static void null_after_eof_checks(int fd)
{
    char *p;
    int k;

    for (k = 1; k <= 3; k++)
    {
        p = get_next_line(fd);
        printf("NULL check %d -> %s\n", k, (p == NULL) ? "NULL (OK)" : "NOT NULL (BUG)");
        free(p);
    }
}

int main(int argc, char **argv)
{
    const char *path = (argc > 1) ? argv[1] : "multiple_nl.txt";
    int fd;
    char *line;
    int i = 1;

    if (strcmp(path, "-") == 0)
        fd = STDIN_FILENO;
    else
        fd = open(path, O_RDONLY);

    if (fd < 0)
    {
        fprintf(stderr, "open('%s') failed: %s\n", path, strerror(errno));
        return 1;
    }

#ifdef BUFFER_SIZE
    printf("BUFFER_SIZE = %d\n", BUFFER_SIZE);
#else
    printf("BUFFER_SIZE (default)\n");
#endif

    while ((line = get_next_line(fd)) != NULL)
    {
        size_t len = strlen(line);
        printf("[%d] len=%zu: \"", i++, len);
        print_visible(line);
        puts("\"");
        free(line);
    }

    /* run a few extra NULL-after-EOF calls to catch the KO segfault */
    null_after_eof_checks(fd);

    if (fd != STDIN_FILENO)
        close(fd);
    return 0;
}
