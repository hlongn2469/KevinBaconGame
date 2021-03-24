// BaconManager.h
// @Author: Kray Nguyen
// 2/5/2021
// Class that extracts actor names and movie names from files and store 
// those information into a map for graph implementation
#include "Graph.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <sstream>
#include <algorithm>
#include <stdio.h>
#include <map>

using namespace std;

class BaconManager{
public:
    // @param {ifstream} fileName - file name of the actor and movie names
    // @pre: BaconManager object is created
    // @post: the output is printed with each line containing each actor and their bacon number
    // @return: none
    // @function called: map.push_back(), excludeOptional(), linkActor(), findIndex(); findKevinIndex();
    void processFile(ifstream &fileName);


private:
    // store lists of actor and keep track of indexes
    vector<string> actor_list;

    // store lists of bacon numbers and keep track of indexes
    vector<int> bacon_list;

    // map construction for later graph implementation
    map<string, vector<string>> Map;

    // Graph object intialized
    Graph graph;

    // index of kevin bacon in actor_list
    int bacon_index;

    // @param {string} word - movie needs to be cleaned
    // @pre: word string is valid
    // @post: movie name is cleaned
    // @return: clean string of movies
    // @function called: none
    void excludeOptional(string& word);

    // @param {vector<LList>&} vertex_list - vertex list of actos
    // @pre: vertex list is constructed
    // @post: add an edge for every 2 actors that is in each vertexlist
    // @return: none
    // @function called: graph.addEdge()
    void linkActor(vector<vector<int>>&vertex_list);

    // @param {string} actor - actor name that needs to find index 
    // @pre: string actor is valid
    // @post: none
    // @return: int index of the actor in the actor_list
    // @function called: none
    int findIndex(string actor);

    // @pre: actor_list is created
    // @post: none
    // @return: int index of the kevin bacon in the actor_list
    // @function called: none
    int findKevinIndex();

};