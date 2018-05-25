//
// Created by Cole Shepherd on 4/16/18.
//

#include "Queue.h"

Queue::Queue(int n) {
    for (int i=1; i <= n; i++){
        q.push(i);
    }
}

int Queue::remove() {
    mtx.lock();
    int frnt = q.front();
    q.pop();
    mtx.unlock();
    return frnt;

}

bool Queue::isEmpty() {
    return q.empty();
}

