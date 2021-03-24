// Graph.h
// @Author: Kray Nguyen
// 2/5/2021
// Graph implementation using adjacency list approach to link mutual connections to each actor
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

class Graph {
public:
    Graph();
    Graph(int vertices);
    ~Graph();
    
    // @param {vector<LList>&} vertex_list - adjacency presentation of the graph
    // @param {int} v1_index - index of first actor to link
    // @param {int} v2_index - index of second actor to link
    // @pre: vertex_list is initialized
    // @post: the 2 actors contain a mutual link
    // @return: None
    // @function called: LList.insertFront();
    void addEdge(vector<vector<int>>&vertex_list, int v1_index, int v2_index);

    // @param {vector<string>} actor_list - list of actors retrieved from the file
    // @pre: actor_list is initialized
    // @post: the actor_list inside the graph class is set
    // @return: true
    // @function called: none
    bool setActorList(vector<string> actor_list);

    // @pre: actor_list and bacon_list is filled with values with regards to the actors
    // @post: the output is printed with each actor and their bacon number
    // @return: none
    // @function called: none
    void printGraph();

    // @param {vector<LList>&} vertex_list - adjacency presentation of the graph
    // @param {int} source - index of source actor to find links to
    // @param {int} target - index of target actor to link with the source actor
    // @param {int} num_vertex - number of vertexes 
    // @param {int[]} distance- array storing the distance to compare between different paths
    // @param {int[]} previous - array storing previous visited actor index
    // @pre: vertex_list is initialized
    // @post: the 2 actors contain a mutual link
    // @return: None
    // @function called: LList.getActor(), vector.push_back()
    bool calculateBacon(vector<vector<int>>vertex_list, int source, int target, int num_vertex, int distance[], int previous[]);

    // @param {vector<LList>&} vertex_list - adjacency presentation of the graph
    // @param {int} source - index of source actor to find links to
    // @param {int} target - index of target actor to link with the source actor
    // @param {int} num_vertex - number of vertexes 
    // @pre: vertex_list is initialized
    // @post: the 2 actors contain a mutual link
    // @return: None
    // @function called: calculateBacon()
    void BaconHelper(vector<vector<int>>vertex_list, int source, int target, int num_vertex);

private:
    // store actors and to keep track of actor indexes
    vector<string> actor_list;

    /// store bacon number and keep track of actor indexes
    vector<int> bacon_list;

    // keep track number of vertexes
    int num_vertex;

    // keep track number of edges
    int num_edges;
};