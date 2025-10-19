#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

char *get_next_line(int fd);

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

static int write_n_newlines(const char *path, int n)
{
    int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        fprintf(stderr, "open('%s') for write failed: %s\n", path, strerror(errno));
        return 0;
    }
    char buf[1024];
    memset(buf, '\n', sizeof(buf));
    int left = n;
    while (left > 0)
    {
        int chunk = left > (int)sizeof(buf) ? (int)sizeof(buf) : left;
        if (write(fd, buf, chunk) != chunk)
        {
            fprintf(stderr, "write failed\n");
            close(fd);
            return 0;
        }
        left -= chunk;
    }
    close(fd);
    return 1;
}

static int run_multiple_nl(const char *path, int extra_calls)
{
    int fd = open(path, O_RDONLY);
    if (fd < 0)
    {
        fprintf(stderr, "open('%s') failed: %s\n", path, strerror(errno));
        return 0;
    }

#ifdef BUFFER_SIZE
    printf("BUFFER_SIZE = %d\n", BUFFER_SIZE);
#endif
    printf("File: %s\n", path);

    char *line;
    int i = 1;
    while ((line = get_next_line(fd)) != NULL)
    {
        size_t len = strlen(line);
        printf("[%d] len=%zu: \"", i++, len);
        print_visible(line);
        puts("\"");
        free(line);
    }

    int ok = 1;
    for (int k = 1; k <= extra_calls; k++)
    {
        line = get_next_line(fd);
        if (line != NULL)
        {
            printf("[KO] extra call #%d returned non-NULL: \"", k);
            print_visible(line);
            puts("\"");
            free(line);
            ok = 0;
            break;
        }
    }
    if (ok)
        printf("[OK] %d extra calls after EOF all returned NULL\n", extra_calls);

    close(fd);
    return ok;
}

int main(int argc, char **argv)
{
    int count = 5;
    int extra = 32;
    const char *path = "zz_multiple_nl.txt";

    if (argc > 1) count = atoi(argv[1]);
    if (argc > 2) extra = atoi(argv[2]);
    if (argc > 3) path = argv[3];

    if (count < 0) count = 0;
    if (!write_n_newlines(path, count))
        return 1;

    return run_multiple_nl(path, extra) ? 0 : 1;
}
