#include <iostream>
#include <list>
#include <pthread.h>

class Node {
public:
    Node(int value) : data(value) {
        pthread_mutex_init(&mutex, NULL);
    }

    int GetData() const {
        return data;
    }

    pthread_mutex_t GetMutex() const {
        return mutex;
    }

private:
    int data;
    pthread_mutex_t mutex;
};

class LinkedListPerNode {
public:
    void Member(int value) {

        for (Node& node : nodes) {
            pthread_mutex_lock(&node.GetMutex());
            if (node.GetData() == value) {

                std::cout << "Member: " << value << std::endl;
            }
            pthread_mutex_unlock(&node.GetMutex());
        }
    }

    void Insert(int value) {
        nodes.emplace_back(value);

        std::cout << "Insert: " << value << std::endl;
    }

    void Delete(int value) {
        auto it = std::find_if(nodes.begin(), nodes.end(),
                               [value](const Node& node) { return node.GetData() == value; });
        if (it != nodes.end()) {
            pthread_mutex_lock(&it->GetMutex());

            std::cout << "Delete: " << value << std::endl;
            pthread_mutex_unlock(&it->GetMutex());
            nodes.erase(it);
        }
    }

private:
    std::list<Node> nodes;
};
