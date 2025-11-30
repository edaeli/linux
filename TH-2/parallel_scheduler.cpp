#include "parallel_scheduler.h"
#include <unistd.h> 
#include <iostream>

parallel_scheduler::parallel_scheduler(int capacity)
    : head(0), tail(0), count(0), stop(false)
{
    thread_count = capacity;
    threads = new pthread_t[thread_count];

    pthread_mutex_init(&mutex, nullptr);
    pthread_cond_init(&cond, nullptr);

    for (int i = 0; i < thread_count; i++) {
        pthread_create(&threads[i], nullptr, worker, this);
    }
}

parallel_scheduler::~parallel_scheduler() {
    pthread_mutex_lock(&mutex);
    stop = true;
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mutex);

    for (int i = 0; i < thread_count; i++)
        pthread_join(threads[i], nullptr);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    delete[] threads;
}

void parallel_scheduler::run(task_fn func, void* arg) {
    pthread_mutex_lock(&mutex);

    tasks[tail].func = func;
    tasks[tail].arg  = arg;
    tail = (tail + 1) % 100;
    count++;

    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
}

void* parallel_scheduler::worker(void* arg) {
    auto* self = (parallel_scheduler*)arg;

    while (true) {
        pthread_mutex_lock(&self->mutex);

        while (self->count == 0 && !self->stop) {
            pthread_cond_wait(&self->cond, &self->mutex);
        }

        if (self->stop) {
            pthread_mutex_unlock(&self->mutex);
            return nullptr;
        }

        auto task = self->tasks[self->head];
        self->head = (self->head + 1) % 100;
        self->count--;

        pthread_mutex_unlock(&self->mutex);

        task.func(task.arg);
    }
}

