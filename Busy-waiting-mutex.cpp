#include <iostream>
#include <thread>
#include <mutex>
#include <vector>


int counter = 0; 
int thread_count = 3; 
std::mutex barrier_mutex;

// Función de trabajo del hilo
void ThreadWork(int thread_id) {
    {
        // Sección crítica protegida por el mutex
        std::lock_guard<std::mutex> lock(barrier_mutex);
        counter++;
    }

    // Espera activa hasta que todos los hilos han alcanzado la barrera
    while (counter < thread_count);

    // Todos los hilos han alcanzado la barrera
    std::lock_guard<std::mutex> lock(barrier_mutex);
    std::cout << "Thread " << thread_id << " Llegó a la barrera." << std::endl;
}

int main() {

    std::vector<std::thread> threads;
    for (int i = 0; i < thread_count; ++i) {
        threads.emplace_back(ThreadWork, i);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    std::cout << "Todos los hilos llegaron a la barrera." << std::endl;

    return 0;
}
