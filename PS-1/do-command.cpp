#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <chrono>

void do_command(char** argv) {
    auto start = std::chrono::high_resolution_clock::now();

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return;
    }

    if (pid == 0) {
        execvp(argv[0], argv);
        perror("execvp");
        _exit(1);
    } else {
        int status;
        waitpid(pid, &status, 0);

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;

        int exit_code = WIFEXITED(status) ? WEXITSTATUS(status) : -1;
        std::cout << "Command completed with " 
                  << exit_code << " exit code and took " 
                  << duration.count() << " seconds." << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <command>" << std::endl;
        return 1;
    }

    do_command(argv + 1);

    return 0;
}

