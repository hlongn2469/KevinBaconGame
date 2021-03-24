// main.cpp
// @Author: Kray Nguyen
// 2/5/2021
// Input: file name of the actor file within the directory
// Output: Bacon number of each actor that appears in the file
// Usage: ./a.out fileName.txt
// Assumption: Only find actor connections to Kevin Bacon (I)
// Assumption: the program stops if not found the actor file
// Major algorithms: BFS shortest paths between a source actor to a target actor 
// Major algorithms: LList of each actor storing chains of actors that have mutual connections

#include <string>
#include <iostream>
#include <typeinfo>
#include <ostream>
#include <fstream>
#include <vector>
#include "BaconManager.h"

using namespace std;

int main(int argc, char *argv[]){
    // Manager object to manipulate operations
    BaconManager manager;

    // get command line name 
    string fileName = argv[1];

    ifstream file(fileName);
    manager.processFile(file);

    return 0;
}   