// Graph.cpp
// @Author: Kray Nguyen
// 2/5/2021
// Graph implementation using adjacency list approach to link mutual connections to each actor
#include "Graph.h"
#include <string>
#include <climits>
#include <queue>

using namespace std; 

Graph::Graph(){
    this -> num_edges = 0;
    this -> num_vertex = 0;
}

Graph::~Graph(){

}

Graph::Graph(int vertex){
    // set num_vertex
    this ->num_vertex = vertex;
}

// @param {vector<LList>&} vertex_list - adjacency presentation of the graph
// @param {int} v1_index - index of first actor to link
// @param {int} v2_index - index of second actor to link
// @pre: vertex_list is initialized
// @post: the 2 actors contain a mutual link
// @return: None
// @function called: LList.insertFront();
void Graph::addEdge(vector<vector<int>>&vertex_list, int source, int destination){
    // add source to destination
    vertex_list.at(source).push_back(destination);

    // add destination to source, as for undirected graph
    vertex_list.at(destination).push_back(source);
    
}

// @param {vector<string>} actor_list - list of actors retrieved from the file
// @pre: actor_list is initialized
// @post: the actor_list inside the graph class is set
// @return: true
// @function called: none
bool Graph::setActorList(vector<string> list){
    actor_list = list;
    return true;
}

// @pre: actor_list and bacon_list is filled with values with regards to the actors
// @post: the output is printed with each actor and their bacon number
// @return: none
// @function called: none
void Graph::printGraph(){
    // for(int i = 0; i < vertex_list.size(); i++){
    //     cout << "Vertex " << i << " is connected to : " << vertex_list[i] << endl;
    // }
    for(int i = 0; i < actor_list.size(); i++){
        if(bacon_list[i] == 100000){
            cout << actor_list[i] << ": infinity" << endl;
        } else {
            cout << actor_list[i] << ": " << bacon_list[i] << endl;
        }
    }
}

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
bool Graph::calculateBacon(vector<vector<int>>vertex_list, int source, int target, int num_vertex, int* previous, int* distance){
    // queue used to process vertices that their adjacency list needs to be checked
    queue<int> q;

    // store whether the vertex is visited at least once 
    bool visited[num_vertex];
    
    // default initialization
    for (int i = 0; i < num_vertex; i++) {
        visited[i] = false;
        distance[i] = INT_MAX;
        previous[i] = -1;
    }

    // visit the source first 
    q.push(source);

    // set source distance to 0
    distance[source] = 0;

    // mark source visited
    visited[source] = true;
    
    // BFS algorithm
    while(!q.empty()){
        // get current actor
        int current_actor = q.front();

        // pop the retreived actor from the queue
        q.pop();
        for(int i = 0; i < vertex_list[current_actor].size();i++){
            // if the current actor is not visited
            if(visited[vertex_list[current_actor].at(i)] == false){
                // mark current actor as visited
                visited[vertex_list[current_actor].at(i)] = true;

                // push the adjacent actors to the queue
                q.push(vertex_list[current_actor].at(i));

                // distance will be added by 1 for each adjacent actor in the linked list
                distance[vertex_list[current_actor].at(i)] = distance[current_actor] + 1;

                //mark current actor to the previous list
                previous[vertex_list[current_actor].at(i)] = current_actor;
                
            }
            // target actir found
            if(vertex_list[current_actor].at(i) == target){
                return true;
            }
        }
    }
    return false;
}


// @param {vector<LList>&} vertex_list - adjacency presentation of the graph
// @param {int} source - index of source actor to find links to
// @param {int} target - index of target actor to link with the source actor
// @param {int} num_vertex - number of vertexes 
// @pre: vertex_list is initialized
// @post: the 2 actors contain a mutual link
// @return: None
// @function called: calculateBacon()
void Graph::BaconHelper(vector<vector<int>> vertex_list, int source, int target, int num_vertex){
    // array storing the distance to compare between different paths
    
    int distance[num_vertex];

    // array storing previous visited actor index
    int previous[num_vertex];

    // to assign values to cases with no connection to Kevin Bacon
    int infinity = 100000;

    // if no connection to kevin Bacon
    if(!calculateBacon(vertex_list, source, target, num_vertex, previous, distance)){
        bacon_list.push_back(infinity);
        return;
    } else {
        int bacon_num = distance[target];
        bacon_list.push_back(bacon_num);
    }

}