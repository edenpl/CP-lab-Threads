#include <iostream>
#include <thread>
#include <mutex>
#include <shared_mutex>

class Node {
  public:
    int data;
    Node* next;
    std::mutex mutex;

    Node(int data) {
      this->data = data;
      this->next = nullptr;
    }
};

class LinkedList {
  private:
    Node* head;
    

    std::shared_mutex rw_locks;
    std::mutex one_mutex;  

  public:
    LinkedList() {
      head = nullptr;
    }

    // rw_locks
    void insert_rw(int data) {
      std::unique_lock<std::shared_mutex> lock(rw_locks);
      
      Node* nuevo = new Node(data);
      nuevo->next = head;
      head = nuevo;
    }

    bool contains_rw(int data) {
      std::shared_lock<std::shared_mutex> lock(rw_locks);
      
      Node* actual = head;
      while (actual != nullptr) {
        if (actual->data == data) {
          return true;
        }
        actual = actual->next; 
      }
      return false;
    }

    void delete_rw(int data) {
      std::unique_lock<std::shared_mutex> lock(rw_locks);
      

    }

    // one_mutex
    void insert_one(int data) {
      std::lock_guard<std::mutex> lock(one_mutex);
      
      // Igual que insert_rw
    }

    bool contains_one(int data) {
      std::lock_guard<std::mutex> lock(one_mutex);

      // Igual que contains_rw
    }

    void delete_one(int data) {
      std::lock_guard<std::mutex> lock(one_mutex);

      // Igual que delete_rw      
    }


    void insert_node(int data) {
      // Lock head
      std::lock_guard<std::mutex> lock_head(head->mutex);
      

    }

    bool contains_node(int data) {

      std::lock_guard<std::mutex> lock_head(head->mutex);
      
      Node* actual = head;

      while(actual != nullptr) {

      }

      return false;
    }

    void delete_node(int data) {
  
    }
};



int main() {
  LinkedList list;
  std::thread threads[8];
  for (int i=0; i<8; i++) {
    threads[i] = std::thread([&]() {

    });
  }
  for (int i=0; i<8; i++) {
    threads[i].join();
  }

  return 0;
}