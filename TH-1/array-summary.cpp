#include <iostream>
#include <vector>
#include <pthread.h>
#include <chrono>
#include <cstdlib>

struct ThreadData {
    const int* arr;
    long long start;
    long long end;
    long long partialSum;
};

void* sumArrayPart(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    long long sum = 0;
    for (long long i = data->start; i < data->end; ++i) {
        sum += data->arr[i];
    }
    data->partialSum = sum;
    return nullptr;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " N M\n";
        return 1;
    }

    long long N = atoll(argv[1]); 
    int M = atoi(argv[2]);        

    if (N <= 0 || M <= 0) {
        std::cerr << "N and M must be positive numbers.\n";
        return 1;
    }

    std::vector<int> arr(N);
    for (long long i = 0; i < N; ++i) {
        arr[i] = rand() % 100; 
    }
    auto startSingle = std::chrono::high_resolution_clock::now();

    long long sumSingle = 0;
    for (long long i = 0; i < N; ++i) {
        sumSingle += arr[i];
    }

    auto endSingle = std::chrono::high_resolution_clock::now();
    double durationSingle = std::chrono::duration<double>(endSingle - startSingle).count();

    auto startMulti = std::chrono::high_resolution_clock::now();

    std::vector<pthread_t> threads(M);
    std::vector<ThreadData> threadData(M);

    long long chunkSize = N / M;

    for (int i = 0; i < M; ++i) {
        threadData[i].arr = arr.data();
        threadData[i].start = i * chunkSize;
        threadData[i].end = (i == M - 1) ? N : (i + 1) * chunkSize;
        threadData[i].partialSum = 0;

        pthread_create(&threads[i], nullptr, sumArrayPart, &threadData[i]);
    }

    long long totalSum = 0;
    for (int i = 0; i < M; ++i) {
        pthread_join(threads[i], nullptr);
        totalSum += threadData[i].partialSum;
    }

    auto endMulti = std::chrono::high_resolution_clock::now();
    double durationMulti = std::chrono::duration<double>(endMulti - startMulti).count();

    std::cout << "Time spent without threads: " << durationSingle << " seconds" << std::endl;
    std::cout << "Time spent with " << M << " threads: " << durationMulti << " seconds" << std::endl;


    return 0;
}

