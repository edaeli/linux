#include <iostream>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <cstdlib>

void initialize(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input-file>\n";
        exit(1);
    }

    const char* filename = argv[1];
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        exit(1);
    }

    if (dup2(fd, STDIN_FILENO) == -1) {
        perror("Error redirecting stdin");
        close(fd);
        exit(1);
    }

    close(fd);
}

int main(int argc, char** argv)
{
    initialize(argc, argv);

    std::string s;
    std::cin >> s;

    std::string reversed(s.rbegin(), s.rend());
    std::cout << reversed << std::endl;

    return 0;
}

