#include <iostream>
#include <list>
#include <pthread.h>

class LinkedListOneMutex {
public:
    LinkedListOneMutex() {
        pthread_mutex_init(&mutex, NULL);
    }

    void Member(int value) {
        pthread_mutex_lock(&mutex);

        std::cout << "Member: " << value << std::endl;
        pthread_mutex_unlock(&mutex);
    }

    void Insert(int value) {
        pthread_mutex_lock(&mutex);

        std::cout << "Insert: " << value << std::endl;
        pthread_mutex_unlock(&mutex);
    }

    void Delete(int value) {
        pthread_mutex_lock(&mutex);

        std::cout << "Delete: " << value << std::endl;
        pthread_mutex_unlock(&mutex);
    }

private:
    std::list<int> list;
    pthread_mutex_t mutex;
};
