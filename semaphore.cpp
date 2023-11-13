#include <iostream>
#include <thread>
#include <semaphore.h>
#include <vector>
#include <mutex>



int counter = 0; 
int thread_count = 3; 
sem_t count_sem, barrier_sem; // Semáforos
std::mutex counter_mutex; 


void ThreadWork(int thread_id) {
    // Sección crítica protegida por mutex para incrementar el contador
    {
        std::lock_guard<std::mutex> lock(counter_mutex);
        counter++;
    }

    // Esperar a que todos los hilos hayan llegado a la barrera
    sem_wait(&count_sem);


    if (counter == thread_count - 1) {
        // Resetear el contador y liberar el semáforo count_sem
        {
            std::lock_guard<std::mutex> lock(counter_mutex);
            counter = 0;
        }
        sem_post(&count_sem);

        for (int j = 0; j < thread_count - 1; j++) {
            sem_post(&barrier_sem);
        }
    } else {

        {
            std::lock_guard<std::mutex> lock(counter_mutex);
            counter++;
        }
        sem_post(&count_sem);


        sem_wait(&barrier_sem);
    }



    std::cout << "Thread " << thread_id << " completed work." << std::endl;
}

int main() {
    // Inicialización de semáforos
    sem_init(&count_sem, 0, 1);   
    sem_init(&barrier_sem, 0, 0); 

    // Inicialización de hilos
    std::vector<std::thread> threads;
    for (int i = 0; i < thread_count; ++i) {
        threads.emplace_back(ThreadWork, i);
    }

    // Esperar a que todos los hilos terminen
    for (auto& thread : threads) {
        thread.join();
    }

    // Destruir los semáforos
    sem_destroy(&count_sem);
    sem_destroy(&barrier_sem);

    return 0;
}
