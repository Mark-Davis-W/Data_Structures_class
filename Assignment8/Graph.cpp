//CS1300 Fall 2019
//Author: Mark Davis
//Recitation:203 Divya
//Homework #8

#include <iostream>
#include <math.h>
#include <cmath>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <string>
#include <stdlib.h>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <locale>
#include <vector>
#include <queue>
#include "Graph.hpp"

using namespace std;

void Graph::addEdge(string v1, string v2){//make connections b/n vertexes
  for(int i = 0; i < vertices.size(); i++){
      if(vertices[i]->name == v1){
          for(int j = 0; j < vertices.size(); j++){
              if(vertices[j]->name == v2 && i != j){
                  adjVertex av;
                  av.v = vertices[j];
                  vertices[i]->adj.push_back(av);
                  //another vertex for edge in other direction
                  adjVertex av2;
                  av2.v = vertices[i];
                  vertices[j]->adj.push_back(av2);
              }
          }
      }
  }
}

void Graph::addVertex(string n){//add vertex node
  bool found = false;
  for(int i = 0; i < vertices.size(); i++){
      if(vertices[i]->name == n){
          found = true;
      }
  }
  if(!found){
      vertex * v = new vertex;
      v->name = n;
      vertices.push_back(v);
  }
}

void Graph::displayEdges(){//print edges

  for(unsigned int i = 0; i < vertices.size(); i++){
      cout << vertices[i]->name << " --> ";
      for(unsigned int j = 0; j < vertices[i]->adj.size(); j++){
          cout << vertices[i]->adj[j].v->name << " ";
      }
      cout << endl;
  }

  /* Formatting
  Boulder --> Denver
  Denver --> Boulder Las Vegas
  Las Vegas --> Denver */
}

void Graph::breadthFirstTraverse(string start){//traverse and print
  // A pointer for source vertex
  vertex *vStart;

  for(unsigned int i = 0; i < vertices.size(); i++){
    if(vertices[i]->name == start){
        vStart = vertices[i];
    }
  }

  vStart->visited = true;
  queue<vertex*> q;
  q.push(vStart);
  vertex* n;

  // for the source vertex in the graph
  cout<< "Starting vertex (root): " << vStart->name << "-> ";

  while(!q.empty()){
    n = q.front(); //save last entry of queue value to n
    q.pop(); //remove first entry after each loop
    // go to all the adjacent vertices of n
    for(unsigned int x = 0; x < n->adj.size(); x++ ){
      // If a adjacent has not been visited, then mark it visited and enqueue it
      if(!(n->adj[x].v->visited)){
        q.push(n->adj[x].v);
        n->adj[x].v->visited = true;
        // cout << "adding: " << n->adj[x].v->distance << " + 1 " << ", x: " << x << endl;
        // cout << "n distance: " << n->distance << endl;
        n->adj[x].v->distance = n->distance +1;
        // for other vertex traversed from source vertex with distance
        cout << n->adj[x].v->name <<"("<< n->adj[x].v->distance <<")"<< " ";
      }
    }
    n->distance += 1;
  }
}

void getComponentsHelper(vertex* n){//Depth First Traversal
  n->visited = true;
  //cout << "vertices: " << n->name << " visited: " << n->visited << endl;

  for(unsigned int x = 0; x < n->adj.size(); x++ ){
    if(!n->adj[x].v->visited){
      getComponentsHelper(n->adj[x].v); //need recursion to find all linked vertex
      //cout << "adj: " << n->adj[x].v->name << " visited: " << n->adj[x].v->visited << endl;
    }
  }
}

int Graph::getConnectedComponents(){ //find number of subtrees
  int unconnected = 0;
  for(unsigned int i = 0; i < vertices.size(); i++){
    if(!vertices[i]->visited){
      getComponentsHelper(vertices[i]);
      unconnected++;
    }
  }
  return unconnected;
}

void checkBiPartiteHelp(vertex* n){ //recursive used to color
  n->visited = true;
  if(n->color == ""){//if empty must be parent, color
    n->color = "red";
  }
  //cout << "vertices: " << n->name << " color: " << n->color << endl;

  for(unsigned int x = 0; x < n->adj.size(); x++ ){ //go through all the adj nodes

    if(!n->adj[x].v->visited){
      n->adj[x].v->visited = true;
      if(n->color == "red"){//color adj nodes according to parent
        (n->adj[x].v)->color = "green";
      }
      if(n->color == "green"){//color adj nodes according to parent
        (n->adj[x].v)->color = "red";
      }
      //cout << "adj: " << n->adj[x].v->name << " color: " << n->adj[x].v->color << endl;
      //checkBiPartiteHelp(n->adj[x].v); //no need for recursion but works with it
    }
  }
}

bool checkBiPartiteColor(vertex* n){//checking color validity
    for(unsigned int x = 0; x < n->adj.size(); x++){
      if(n->color == (n->adj[x].v)->color){
        return false;
      }
    }
  return true;
}

bool Graph::checkBipartite(){//set & then check colors are valid
  for(unsigned int i = 0; i < vertices.size(); i++){
    if(!vertices[i]->visited){
      checkBiPartiteHelp(vertices[i]);
    }
  }
  for(unsigned int i = 0; i < vertices.size(); i++){
    if(!checkBiPartiteColor(vertices[i]))
      return false;
  }

  return true;

  //if color is not set, set according to parent (edge case is root)
  //else check adj list comparing colors
  //recursive will traverse and check all?? BFS but maybe DFS since interconnected (faster?)
}
