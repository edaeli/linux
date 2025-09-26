#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    const char *path = argv[1];
    int fd = open(path, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Error opening '%s': %s\n", path, strerror(errno));
        return 1;
    }

    char buffer[4096];
    ssize_t bytes_read;
    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        ssize_t total_written = 0;
        while (total_written < bytes_read) {
            ssize_t written = write(STDOUT_FILENO, buffer + total_written, bytes_read - total_written);
            if (written == -1) {
                fprintf(stderr, "Write error: %s\n", strerror(errno));
                close(fd);
                return 1;
            }
            total_written += written;
        }
    }

    if (bytes_read == -1) {
        fprintf(stderr, "Read error: %s\n", strerror(errno));
        close(fd);
        return 1;
    }

    close(fd);
    return 0;
}

