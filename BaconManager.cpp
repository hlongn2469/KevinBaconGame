// BaconManager.cpp
// @Author: Kray Nguyen
// 2/5/2021
// Class that extracts actor names and movie names from files and store 
// those information into a map for graph implementation

#include "BaconManager.h"
#include <string.h>

// @param {ifstream} fileName - file name of the actor and movie names
// @pre: BaconManager object is created
// @post: the output is printed with each line containing each actor and their bacon number
// @return: none
// @function called: map.push_back(), excludeOptional(), linkActor(), findIndex(); findKevinIndex();
void BaconManager::processFile(ifstream& fileName){
    // if file not found
    if(!fileName){
        cerr << "File not found, end the program now" << endl;
    }
    
    // initialize variables for later uses for memory savings
    string line_description, actor_name, movie_name, copy_text;

    // for each line of texts
    while(getline(fileName,line_description)){
        bool getName = false;

        stringstream copy(line_description);

        // for each sub-lines - for multiple movies of each actor
        while(getline(copy,copy_text, '\t')){
            // if hasn't got the name and the first line is not tab indented
            if(!getName && line_description[0] != '\t'){
                // mark got name
                getName = true;

                // actor name found
                actor_name = copy_text;

                // push actor name to list
                actor_list.push_back(actor_name);

            // if the subline is not empty
            } else if (copy_text != "\0"){
                // clean optional info from the text
                excludeOptional(copy_text);

                // movie name found
                movie_name = copy_text;
                
                // push all actor names as value to key as movie name to maps
                Map[movie_name].push_back(actor_name);
            }
            // strip duplicates values from the map
            sort( Map[movie_name].begin(), Map[movie_name].end() );
            Map[movie_name].erase( unique( Map[movie_name].begin(), Map[movie_name].end() ), Map[movie_name].end() );
        }
    }

    // intialize graph equals to actor_list size
    Graph graph(actor_list.size());

    // intialize the vertex_list for graph implementation
    vector<vector<int>> vertex_list(actor_list.size());

    // set actor_list inside graph class
    graph.setActorList(actor_list);

    // link every values to each other given the same key 
    linkActor(vertex_list);

    // get kevin bacon index
    bacon_index = findKevinIndex();
    
    // calculate bacon number for each actor
    for(int i = 0; i < actor_list.size();i++){
        graph.BaconHelper(vertex_list, bacon_index, findIndex(actor_list[i]), actor_list.size());
    }

    // print output
    graph.printGraph();
}

// @param {string} word - movie needs to be cleaned
// @pre: word string is valid
// @post: movie name is cleaned
// @return: none
// @function called: none
void BaconManager::excludeOptional(string& word){
    // holding values for movie extraction
    string temp, ret_val;
    string movie_name = word;
    istringstream ss(movie_name);

    // for each " " in the line
    while(ss >> temp){
        // if weird characters is detected at the beginning
        if(temp[0] == '[' || temp[0] == '{' || temp[0] == '(' || temp[0] == '<'){
            // if "("
            if(temp[0] == '('){
                // take the year only, ignore the rest
                ret_val += temp + " ";
            }
            break;
        } else {
            ret_val += temp + " ";
        }
    }
    word = ret_val;   
}

// @param {string} actor - actor name that needs to find index 
// @pre: string actor is valid
// @post: none
// @return: int index of the actor in the actor_list
// @function called: none
int BaconManager::findIndex(string actor){
    for(int i = 0; i < actor_list.size();i++){
        if(actor_list[i] == actor){
            return i;
        }
    }
    return 0;
}

// @pre: actor_list is created
// @post: none
// @return: int index of the kevin bacon in the actor_list
// @function called: none
int BaconManager::findKevinIndex(){
    for(int i = 0; i < actor_list.size();i++){
        if(actor_list[i] == "Bacon, Kevin (I)"){
            return i;
        }
    }
    return 0;
}

// @param {vector<LList>&} vertex_list - vertex list of actos
// @pre: vertex list is constructed
// @post: add an edge for every 2 actors that is in each vertexlist
// @return: none
// @function called: graph.addEdge()
void BaconManager::linkActor(vector<vector<int>>&vertex_list){
    // store actors that needed to be linked
    string actor1,actor2;

    // store size of the linked list and indexes of the 2 actors in the actor_list
    int size, actor1_index, actor2_index;

    // for each key
    for(auto const& x : Map){
        size = x.second.size();
        if(size > 1){
            // add edges between 2 actors 
            for(int i = 0; i < size - 1;i++){
                for(int j = i + 1; j < size;j++){
                    actor1 = x.second[i];
                    actor2 =  x.second[j];
                    actor1_index = findIndex(actor1);
                    actor2_index = findIndex(actor2);
                    graph.addEdge(vertex_list, actor1_index, actor2_index);
                }
            }
        }
    }
}