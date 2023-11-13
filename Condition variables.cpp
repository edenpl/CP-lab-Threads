#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>


int counter = 0;
int thread_count = 3;
std::mutex mutex;
std::condition_variable cond_var;


void ThreadWork(int thread_id) {
    // Sección crítica protegida por mutex para incrementar el contador
    {
        std::unique_lock<std::mutex> lock(mutex);
        counter++;
        if (counter == thread_count) {
            counter = 0;
            cond_var.notify_all();
        } else {
            cond_var.wait(lock, [&] { return counter == 0; });
        }
    }


    std::cout << "Thread " << thread_id << " completed work." << std::endl;
}

int main() {
    // Inicialización de hilos
    std::vector<std::thread> threads;
    for (int i = 0; i < thread_count; ++i) {
        threads.emplace_back(ThreadWork, i);
    }

    // Esperar a que todos los hilos terminen
    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}


