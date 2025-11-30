#ifndef PARALLEL_SCHEDULER_H
#define PARALLEL_SCHEDULER_H

#include <pthread.h>

class parallel_scheduler {
public:
    using task_fn = void (*)(void*);

    explicit parallel_scheduler(int capacity);
    ~parallel_scheduler();

    void run(task_fn func, void* arg);

private:
    struct Task {
        task_fn func;
        void* arg;
    };

    Task tasks[100];       
    int head, tail;       
    int count;

    pthread_t* threads;
    int thread_count;

    pthread_mutex_t mutex;
    pthread_cond_t cond;

    bool stop;

    static void* worker(void* arg);
};

#endif

