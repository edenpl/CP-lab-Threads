#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

class Barrier {
  public:
    Barrier(int count) : counter(0), thread_count(count) {}

    void wait() {
      std::unique_lock<std::mutex> lock(mutex);
      counter++;
      if (counter < thread_count) {
        cv.wait(lock, [this]{return counter >= thread_count;}); 
      } else {
        counter = 0;
        cv.notify_all();
      }
    }

  private:
    std::mutex mutex;
    std::condition_variable cv;
    int counter;
    int thread_count;
};

void worker(Barrier *barrier, int id) {
  std::cout << "Thread " << id << " antes de la barrera\n";

  barrier->wait();

  std::cout << "Thread " << id << " después de la barrera\n";
}

int main() {
  Barrier barrier(3);

  std::thread t1(worker, &barrier, 1);
  std::thread t2(worker, &barrier, 2); 
  std::thread t3(worker, &barrier, 3);

  t1.join();
  t2.join();
  t3.join();

  return 0;
}