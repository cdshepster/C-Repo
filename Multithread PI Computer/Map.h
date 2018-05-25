//
// Created by Cole Shepherd on 4/16/18.
//

#ifndef COMPUTEPI_MAP_H
#define COMPUTEPI_MAP_H


#include <vector>
#include <mutex>
#include <map>

class Map {
private:
	std::map<int,int> m;
	std::mutex mtx;
public:
    void insert(int key, int value);
    void print();

};


#endif //COMPUTEPI_MAP_H
