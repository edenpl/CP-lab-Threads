#include <iostream>
#include <list>
#include <pthread.h>

class LinkedListRWLock {
public:
    LinkedListRWLock() {
        pthread_rwlock_init(&rwlock, NULL);
    }

    void Member(int value) {
        pthread_rwlock_rdlock(&rwlock);

        std::cout << "Member: " << value << std::endl;
        pthread_rwlock_unlock(&rwlock);
    }

    void Insert(int value) {
        pthread_rwlock_wrlock(&rwlock);

        std::cout << "Insert: " << value << std::endl;
        pthread_rwlock_unlock(&rwlock);
    }

    void Delete(int value) {
        pthread_rwlock_wrlock(&rwlock);

        std::cout << "Delete: " << value << std::endl;
        pthread_rwlock_unlock(&rwlock);
    }

private:
    std::list<int> list;
    pthread_rwlock_t rwlock;
};