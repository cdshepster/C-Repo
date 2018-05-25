//
// Created by Cole Shepherd on 4/16/18.
//

#ifndef COMPUTEPI_QUEUE_H
#define COMPUTEPI_QUEUE_H


#include <queue>
#include <mutex>

class Queue {

private:
    std::queue<int> q;
    std::mutex mtx;

public:
    Queue(int n);
    int remove();
    bool isEmpty();


};


#endif //COMPUTEPI_QUEUE_H
