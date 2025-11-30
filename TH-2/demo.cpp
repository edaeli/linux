#include "parallel_scheduler.h"
#include <iostream>
#include <unistd.h>

void print_task(void* arg) {
    int x = *(int*)arg;
    std::cout << "Task " << x << " running in thread" << std::endl;
    sleep(1);
}

int main() {
    parallel_scheduler pool(3);

    int args[10];
    for (int i = 0; i < 10; i++) {
        args[i] = i;
        pool.run(print_task, &args[i]);
    }

    sleep(5); 
    return 0;
}

