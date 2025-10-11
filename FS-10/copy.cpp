#include <iostream>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {

    if (argc != 3) 
        return std::cerr << "Usage: " << argv[0] << " src dst\n", 1;

    int in = open(argv[1], O_RDONLY);
    int out = open(argv[2], O_WRONLY | O_CREAT,  0644);

    if (in < 0 || out < 0) {
    	perror("error");
	return 1;
    }

    char buf[4096];
    int n;
    long data = 0, hole = 0;

    while ((n = read(in, buf, sizeof(buf))) > 0) {
        for (int i = 0; i < n; ) {
            if (buf[i] == 0) {
                int s = i;
                while (i < n && buf[i] == 0)
		       	i++;
                lseek(out, i - s, SEEK_CUR);
                hole += i - s;
            } else {
                int s = i;
                while (i < n && buf[i] != 0)
		       	i++;
                write(out, buf + s, i - s);
                data += i - s;
            }
        }
    }

    close(in);
    close(out);

    std::cout << "Successfully copied " << (data + hole)
              << " bytes (data: " << data 
              << ", hole: " << hole << ").\n";
}

