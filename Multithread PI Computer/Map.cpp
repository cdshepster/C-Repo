//
// Created by Cole Shepherd on 4/16/18.
//

#include "Map.h"
#include <iostream>

void Map::insert(int key, int value) {
    mtx.lock();
    m.insert(std::make_pair(key, value));
    mtx.unlock();

}

void Map::print() {

	std::cout << "\n" << "\n" << "3.";
    for(int i = 1; i <= m.size(); i++){
		std::cout << m[i];
	}
    std::cout << std::endl;
}
