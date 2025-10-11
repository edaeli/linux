#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <cstring>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file-to-erase>\n";
        exit(1);
    }

    const char* path = argv[1];
    struct stat st;

    if (stat(path, &st) != 0) {
        std::cerr << "no file\n";
        exit(1);
    }

    int fd = open(path, O_WRONLY);
    if (fd < 0) {
        std::cerr << "open error\n";
        exit(1);
    }

    off_t size = st.st_size;
    char zero = '\0';
    for (off_t i = 0; i < size;i++)
        write(fd, &zero, 1);

    close(fd);

    if (unlink(path) != 0) {
        std::cerr << "delete error\n";
        return 4;
    }

    std::cout << "deleted\n";
    return 0;
}

