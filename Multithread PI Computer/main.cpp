#include <iostream>
#include <thread>
#include <vector>
#include <memory>
#include <queue>
#include <unordered_map>
#include <set>
#include <string>

#include "computePi.hpp"
#include "Queue.h"
#include "Map.h"

void threadWorker(Queue &q, Map &m) {

    while(!q.isEmpty()){
		std::cout << '.' << std::flush;
        int digit = q.remove();
        m.insert(digit,computePiDigit(digit));
    }
}

int main() {
	const int NUM = 1000;
    Queue q(NUM);
    Map m;
    
	std::vector<std::shared_ptr<std::thread> > threads;
	for (std::uint16_t core = 0; core < std::thread::hardware_concurrency(); core++)
		threads.push_back(std::make_shared<std::thread>(threadWorker, std::ref(q), std::ref(m)));

	for (auto&& thread : threads)
		thread->join();
		
    m.print();

	return 0;
}
