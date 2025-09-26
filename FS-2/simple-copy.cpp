#include <fcntl.h>    
#include <unistd.h>   
#include <stdio.h>    
#include <stdlib.h> 

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <source-file> <destination-file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char* src = argv[1];
    const char* dst = argv[2];

    int fd_src = open(src, O_RDONLY);
    if (fd_src == -1) {
        perror("open Error");
        exit(EXIT_FAILURE);
    }

   
    int fd_dst = open(dst, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_dst == -1) {
        perror("open Error");
        close(fd_src);
        exit(EXIT_FAILURE);
    }

    char buffer[4096];
    ssize_t bytes_read;

    while ((bytes_read = read(fd_src, buffer, sizeof(buffer))) > 0) {
        ssize_t bytes_written = write(fd_dst, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("error");
            close(fd_src);
            close(fd_dst);
            exit(EXIT_FAILURE);
        }
    }

    if (bytes_read == -1) {
        perror("read error");
    }

    close(fd_src);
    close(fd_dst);

    return 0;
}

